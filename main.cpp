#include <iostream>
#include <string>
#include <cstdlib> // 用於隨機數生成函數 rand() 和 srand()
#include <ctime>   // 用於獲取當前時間作為隨機種子
#include <unistd.h> // 用於 sleep() 函數來控制遊戲更新頻率
#include <vector>
#include <conio.h>  // Windows特有函式庫，提供 kbhit() 和 getch() 用於即時鍵盤輸入
using namespace std;

// 生成指定範圍內的隨機整數 [n1, n2]
int randBtw(int n1, int n2) {
    return n1 + rand() % (n2 - n1 + 1); // 確保包含端點值
}

// 定義方向鍵的鍵碼常數
#define UP    72
#define DOWN  80
#define LEFT  75
#define RIGHT 77

/**
 * Map類別 - 遊戲世界管理器
 * 負責管理遊戲地圖、分數系統、物件放置和碰撞檢測
 */
class Map
{
private:
    int W, H;                           // 地圖寬度和高度
    int* R;                            // 道路類型陣列，0=一般道路，1=安全區
    const int P = 2;                   // 未使用的參數
    int score = 0;                     // 玩家分數
    vector<vector<char>> grid, g0;     // grid=當前畫面，g0=原始地圖模板
public:
    Map(int w, int h, int* r);         // 建構函數，初始化地圖
    int draw();                        // 繪製遊戲畫面並重置grid
    bool setXY(int x, int y, char c);  // 在指定位置放置物件，包含碰撞檢測
    void addScore(int i) {score += 1;} // 增加分數（參數i實際未使用）
    bool getO(int x, int y);           // 檢查指定位置是否有障礙物
};

/**
 * 檢查指定座標是否存在障礙物
 * 用於移動前的碰撞預測
 * 注意這裡的縮排如何清楚顯示函數內部的邏輯層次
 */
bool Map::getO(int x, int y) {
    if(y >= 0 && y < H && x >= 0 && x < W) {
        if(g0[y][x] == 'O') return true;  // 在原始地圖中檢查障礙物
    }
    return false;
}

/**
 * GameObject抽象基底類別
 * 定義所有遊戲物件的共同介面和屬性
 * 觀察類別定義中的縮排如何幫助區分不同的存取層級
 */
class GameObject
{
protected:
    int x, y;              // 物件座標
    const char c;          // 物件在地圖上的顯示字元
    static Map* map;       // 靜態指標，所有物件共享同一個地圖實例
public:
    GameObject(int x, int y, char c)
        : x(x), y(y), c(c) {setXY(x, y, c);} // 建構時立即在地圖上放置物件
    char getIcon() {return c;}
    int getX() {return x;}
    int getY() {return y;}
    virtual bool move() = 0;           // 純虛擬函數，強制衍生類別實作移動邏輯
    bool setXY(int x, int y, char c);
    static void setMap(Map* m) {map = m;}  // 設定全域地圖實例
    static void draw() {map->draw();}      // 繪製地圖的靜態方法
};

/**
 * GameObject的setXY實作
 * 透過靜態map指標呼叫地圖的setXY方法
 */
bool GameObject::setXY(int x, int y, char c)
{
    if(map) {
        return map->setXY(x, y, c);
    }
    return false;
}

/**
 * Obstacle類別 - 靜態障礙物
 * 不會移動的障礙物，標示為 'O'
 */
class Obstacle : public GameObject
{
public:
    Obstacle(int x, int y) : GameObject(x, y, 'O') {}
    bool move() override {return true;}  // 障礙物不移動，直接返回true
};

/**
 * Vehicle抽象類別 - 載具基底類別
 * 為Car和Moto提供共同的移動方向屬性
 */
class Vehicle : public GameObject
{
protected:
    int d; // 移動方向和速度，正數向右，負數向左
public:
    Vehicle(int x, int y, char c, int d)
        : GameObject(x, y, c) {this->d = d;}
    virtual bool move() = 0;
};

/**
 * Car類別 - 汽車
 * 以完整速度水平移動的載具
 */
class Car : public Vehicle
{
public:
    Car(int x, int y, char c, int d)
        : Vehicle(x, y, c, d) {}
    bool move() override;
};

/**
 * Car的移動邏輯
 * 按照方向d的完整值移動，邊界處環繞
 * 注意條件判斷的縮排如何清楚表達邏輯流程
 */
bool Car::move() {
    x = x + d;                    // 按方向移動
    if(x < 0) x = 39;            // 左邊界環繞到右邊
    if(x > 39) x = 0;            // 右邊界環繞到左邊
    return setXY(x, y, getIcon());
}

/**
 * Moto類別 - 機車
 * 以一半速度移動的載具
 */
class Moto : public Vehicle
{
public:
    Moto(int x, int y, char c, int d)
        : Vehicle(x, y, c, d) {}
    bool move() override;
};

/**
 * Moto的移動邏輯
 * 移動速度是Car的一半（d/2）
 */
bool Moto::move() {
    x = x + d/2;                 // 以一半速度移動
    if(x < 0) x = 39;
    if(x > 39) x = 0;
    return setXY(x, y, getIcon());
}

/**
 * Frog類別 - 玩家控制的青蛙
 * 響應鍵盤輸入進行移動
 */
class Frog : public GameObject
{
public:
    Frog(int x, int y, char c) : GameObject(x, y, c) {}
    bool move() override;
};

/**
 * Frog的移動邏輯
 * 檢測鍵盤輸入並執行移動，包含碰撞檢測和分數計算
 * 這個函數展示了複雜邏輯中縮排的重要性
 */
bool Frog::move() {
    if(kbhit()) {  // 檢查是否有鍵盤輸入（非阻塞）
        int oldX = x, oldY = y;  // 儲存原始位置用於碰撞回復
        char key = getch();      // 獲取按鍵

        // Windows方向鍵需要兩次getch()來完整讀取
        // 注意這裡的多層縮排如何清楚顯示嵌套的邏輯結構
        if (key == -32) {        // 方向鍵的第一個字元
            key = getch();         // 獲取方向鍵的實際代碼
            switch (key) {
                case UP:
                    if(y > 0) y--;     // 向上移動，檢查邊界
                    break;
                case DOWN:
                    if(y < 9) y++;     // 向下移動，檢查邊界
                    break;
                case LEFT:
                    if(x > 0) x--;     // 向左移動，檢查邊界
                    break;
                case RIGHT:
                    if(x < 39) x++;    // 向右移動，檢查邊界
                    break;
            }
        }

        // 碰撞檢測：如果新位置有障礙物，回復到原位置
        if(map->getO(x, y)) {
            x = oldX;
            y = oldY;
        }

        // 如果位置確實改變了，增加分數
        if(x != oldX || y != oldY) map->addScore(1);
    }
    return setXY(x, y, getIcon());
}

/**
 * Map建構函數
 * 初始化遊戲地圖，設定道路和安全區
 * 這裡的for迴圈縮排展示了迴圈結構的清晰性
 */
Map::Map(int w, int h, int* r) : W(w), H(h), R(r) {
    // 初始化基礎地圖，所有位置都是 '.'
    grid = vector<vector<char>>(H, vector<char>(W, '.'));

    // 根據R陣列設定安全區（標示為 '='）
    for(int i = 0; i < H; i++)
        if(R[i] == 1) grid[i] = vector<char>(W, '=');

    g0 = grid;  // 儲存原始地圖狀態

    // 在道路起點放置載具標示
    for(int i = 0; i < H; i++)
    {
        if(R[i] == 0) {  // 如果是道路
            if(i % 2 == 1) grid[i][0] = 'C';      // 奇數列從左側開始
            else grid[i][W - 1] = 'C';            // 偶數列從右側開始
        }
    }
}

/**
 * 繪製遊戲畫面
 * 顯示分數和當前地圖狀態，然後重置grid
 * 巢狀for迴圈的縮排清楚展示了二維遍歷的結構
 */
int Map::draw() {
    cout << "Score: " << score << endl;
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
            cout << grid[i][j];
        cout << endl;
    }
    grid = g0;  // 重置grid到原始狀態，準備下一幀

    return 0;
}

/**
 * 在指定位置放置物件
 * 包含完整的碰撞檢測邏輯
 * 多個條件判斷的縮排幫助理解複雜的邏輯分支
 */
bool Map::setXY(int x, int y, char c) {
    if(y >= 0 && y < H && x >= 0 && x < W) {
        if(c == 'O') g0[y][x] = c;           // 障礙物永久儲存在g0中
        if(c == 'F' && grid[y][x] == 'C') return false;  // 青蛙撞車
        if(c == 'F' && grid[y][x] == 'M') return false;  // 青蛙撞機車
        if(c == 'C' && grid[y][x] == 'F') return false;  // 車撞青蛙
        if(c == 'M' && grid[y][x] == 'F') return false;  // 機車撞青蛙
        grid[y][x] = c;  // 如果沒有碰撞，放置物件
    }
    return true;
}

// 初始化靜態成員變數
Map* GameObject::map = nullptr;

/**
 * 主程式 - 遊戲初始化和主迴圈
 * 這個函數展示了複雜初始化邏輯的縮排重要性
 */
int main()
{
    // 使用當前時間設定隨機種子
    srand(static_cast<unsigned int>(time(0)));

    const int H = 10;   // 地圖高度
    const int W = 40;   // 地圖寬度
    // 道路配置：1=安全區，0=有載具的道路
    int R[H] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 1};

    Map m(W, H, R);           // 建立地圖
    GameObject::setMap(&m);   // 設定全域地圖實例

    vector<GameObject*> GOs;  // 儲存所有遊戲物件的容器

    // 在底部隨機位置建立青蛙
    GOs.push_back(new Frog(randBtw(15, 25), 9, 'F'));

    int x, d;
    // 這個for迴圈展示了複雜初始化邏輯的縮排結構
    for(int i = 0; i < H; i++)
    {
        // 在每列隨機放置一個障礙物
        int ox = randBtw(0, W - 1);
        int oy = randBtw(0, H - 1);
        GOs.push_back(new Obstacle(ox, oy));

        // 在道路上建立載具
        if(R[i] == 0) {
            if(i % 2 == 1) {        // 奇數列：從左到右
                x = 0;
                d = 2;                // 向右移動，速度2
            }
            else {                  // 偶數列：從右到左
                x = W - 1;
                d = -2;               // 向左移動，速度2
            }

            // 偶數列放車，奇數列放機車
            if(i % 2 == 0) GOs.push_back(new Car(x, i, 'C', d));
            else GOs.push_back(new Moto(x, i, 'M', d));
        }
    }

    // 主遊戲迴圈
    // 無限迴圈的內容縮排清楚顯示了遊戲主邏輯
    while(true) {
        system("cls");              // 清除螢幕
        GameObject::draw();         // 繪製遊戲畫面

        // 更新所有遊戲物件
        for(auto o : GOs) {
            if(!o->move()) {          // 如果move()返回false（發生碰撞）
                system("cls");
                usleep(300 * 1000);     // 暫停300毫秒
                cout << "\n\n\n===== GAME OVER =====" << endl;
                return 0;               // 結束遊戲
            }
        }
        usleep(300 * 1000);         // 控制遊戲更新頻率（每秒約3.33幀）
    }

    return 0;
}