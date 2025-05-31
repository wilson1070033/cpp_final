#include "../../include/entities/Frog.h"
#include "../../include/common/GameConstants.h"
#include "../../include/core/LevelManager.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using namespace std;

Frog::Frog(int x, int y, char c) : GameObject(x, y, c) {}

bool Frog::move() {
#ifdef _WIN32
    // Windows 版本
    if(kbhit()) {
        int oldX = x, oldY = y;
        char key = getch();

        if (key == -32) {
            key = getch();
            switch (key) {
                case UP:
                    if(y > 0) y--;
                    break;
                case DOWN:
                    if(y < 9) y++;
                    break;
                case LEFT:
                    if(x > 0) x--;
                    break;
                case RIGHT:
                    if(x < 39) x++;
                    break;
            }
        } else {
            // 處理 WASD 鍵作為備選
            switch(key) {
                case 'w': case 'W':
                    if(y > 0) y--;
                    break;
                case 's': case 'S':
                    if(y < 9) y++;
                    break;
                case 'a': case 'A':
                    if(x > 0) x--;
                    break;
                case 'd': case 'D':
                    if(x < 39) x++;
                    break;
            }
        }

        // 檢查是否撞到障礙物
        if(map->getO(x, y)) {
            x = oldX;
            y = oldY;
        }

        // 如果位置有變化，計算分數
        if(x != oldX || y != oldY) {
            int baseScore = 1;
            int bonusScore = 0;

            // 向上移動（朝目標前進）給予額外分數
            if(y < oldY) {
                bonusScore = 3; // 向前移動獲得更多分數
            }
            // 向下移動（遠離目標）扣除分數
            else if(y > oldY) {
                bonusScore = -1; // 向後移動扣分
            }

            // 獲取關卡管理器以計算關卡加成
            LevelManager* levelMgr = map->getLevelManager();
            if(levelMgr) {
                int levelBonus = levelMgr->getCurrentLevel(); // 關卡越高，移動分數越高
                bonusScore += levelBonus;
            }

            int totalScore = baseScore + bonusScore;
            if(totalScore < 0) totalScore = 0; // 確保分數不會是負數

            map->addScore(totalScore);
        }
    }
#else
    // POSIX 版本（Linux/macOS）
    // 簡化的輸入處理，避免複雜的非阻塞IO
    // 在實際應用中，這裡需要使用ncurses或其他輸入庫
#endif

    return setXY(x, y, getIcon());
}