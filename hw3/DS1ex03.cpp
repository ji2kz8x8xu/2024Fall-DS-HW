#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>

class Pair {
 private:
  int x;
  int y;

 public:
  Pair(int x, int y) {
    this->x = x;
    this->y = y;
  }
  int getPairX() {
    return x;
  }
  int getPairY() {
    return y;
  }
  void printCoord() {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
  }
  
};

class Stack {
 private:
  std::vector<Pair> stack;
 public:
  void push(Pair pair) {
    stack.push_back(pair);
  }

  bool empty() {
    if (stack.size() == 0) {
      return true;
    } else return false;
  }

  Pair top() {
    if (stack.size() == 0) {
      std::cout << "stack empty" << std::endl;
    } else {
      int x ,y;
      x = stack.at(stack.size() - 1).getPairX();
      y = stack.at(stack.size() - 1).getPairY();
      Pair pair(x, y);
      return pair;
    }
  }

  Pair pop() {
    if (stack.size() == 0) {
      std::cout << "stack empty" << std::endl;
    } else {
      int x ,y;
      
      x = stack.at(stack.size() - 1).getPairX();
      y = stack.at(stack.size() - 1).getPairY();
      Pair pair(x, y);
      stack.pop_back();
      return pair;
    }
  }

  int getLength() {
    return stack.size();
  }
};

// 檢查檔案是否存在
bool fileExist(std::string fileName) {
  std::ifstream File(fileName);
  if (!File) {
    return false;
  }
  return true;
}

// check file exist
void checkFileNameExist(std::string& fileName, bool& validName) {
  fileName = "input" + fileName + ".txt";
  validName = fileExist(fileName);
}

// pair相加
std::pair<int, int> sumPair(std::pair<int, int>& pair1, std::pair<int, int>& pair2) {
  return {pair1.first + pair2.first, pair1.second + pair2.second};
}

Pair sumPair(Pair& pair1, Pair& pair2) {
  int x = pair1.getPairX() + pair2.getPairX(), y = pair1.getPairY() + pair2.getPairY();
  Pair pair(x, y);
  return pair;
}

bool pairInVector(std::vector<std::pair<int, int>> pairV, std::pair<int, int> pair) {
  for (auto& ele : pairV) {
    if (ele == pair) {
      return true;
    }
  }
  return false;
}

bool pairEqual(Pair pair1, Pair pair2) {
  if (pair1.getPairX() == pair2.getPairX() && pair1.getPairY() == pair2.getPairY()) return true;
  else return false;
}

bool pairInVector(std::vector<Pair> pairV, Pair pair) {
  for (auto& ele : pairV) {
    if (pairEqual(ele, pair)) {
      return true;
    }
  }
  return false;
}

int getNumOfGoal() {
  std::string goalNum;
  while (1) {
    std::cin >> goalNum;
    if (goalNum[0] == '-') {

    }
  }
}

// 檢查字串是否為有效的數字（可包含負號）
bool isValidNumber(std::string& str) {
  if (str.empty()) return false;
    
  // 檢查第一個字元是否是負號
  size_t start = 0;
  if (str[0] == '-') {
    start = 1;
    if (str.length() == 1) return false; // 僅有負號，不是有效數字
  }

  // 檢查剩下的字元是否都是數字
  for (size_t i = start; i < str.length(); ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

int getNumber(std::string msg) {
  std::string input;
  int num;
  // 小於0在輸一次 大於100 輸出不在範圍[0,100] 不是數字 在輸一次
  while (true) {
    std::cout << std::endl << msg;
    std::cin >> input;
       
    // 檢查是否為有效的數字
    if (isValidNumber(input)) {
      // 將字串轉換為整數
      num = stoi(input);

      // 檢查數字是否在範圍內
      if (num >= 1 && num <= 100) {
        return num;
        // 大於100 或是 0 
      } else if (num > 100 || num == 0) {
        std::cout << std::endl << "### The number must be in [1,100] ###" << std::endl;
        // 小於0或是其他字母
      } else continue;     
    } else continue; 
  }
}

class Maze {
 private:
  int rowSize;
  int colSize;
  // 表示maze 
  bool state;

  // 第一步先向右找
  int lastStepDirection = 0;
  // 輸入為 col*row
  // pair <row, col>
  std::vector<std::vector<char>> mazeData;

 public:

  Maze() {
    state = false;
  }
  // 讀檔案來建構新的maze
  Maze(std::string fileName) {
    readMaze(fileName);
  }
  
  // 利用另一maze建構新的maze
  Maze(Maze& otherMaze) {
    state = true;
    rowSize = otherMaze.getRowSize();
    colSize = otherMaze.getColSize();
    mazeData = otherMaze.getMazeData();
  }

  int getRowSize() {
    return rowSize;
  }

  int getColSize() {
    return colSize;
  }

  int getLastStepDirection() {
    return lastStepDirection;
  }

  std::vector<std::vector<char>> getMazeData() {
    return mazeData;
  }

  bool getState() {
    return state;
  }

  void setRowSize(int rowSize) {
    this->rowSize = rowSize;
  }

  void setColSize(int colSize) {
    this->colSize = colSize;
  }

  void setMazeData(std::vector<std::vector<char>> mazeData) {
    this->mazeData = mazeData;
  }

  void setMazeSymbol(std::pair<int, int> coord, char symbol) {
    mazeData.at(coord.first).at(coord.second) = symbol;
  }

  void setState(bool state) {
    this->state = state;
  }

  bool readMaze(std::string &fileName) {
    std::ifstream inputFile(fileName);

    // 讀取迷宮大小
    std::string line;
    getline(inputFile, line);
    std::istringstream iss(line);

    std::string row, col;
    getline(iss, col, ' ');
    colSize = stoi(col);
    getline(iss, row, ' ');
    rowSize = stoi(row);

    // 初始化 mazeData 為 rowSize x colSize 的二維向量 X 表示未載入地圖
    mazeData.resize(rowSize, std::vector<char>(colSize, 'X'));

    int rowIndex = 0;
    while (getline(inputFile, line) && rowIndex < rowSize) {
      for (int colIndex = 0; colIndex < colSize && colIndex < line.size(); colIndex++) {
        mazeData.at(rowIndex).at(colIndex) = line.at(colIndex);
      }
      rowIndex++;
    }

    inputFile.close();
    state = true;
    return true;
  }

  void printMaze() {
    for (auto &row : mazeData) {
      for (auto &cell : row) {
        std::cout << cell;
      }
      std::cout << std::endl;
    }
  }

  // 先走還沒走過的路
  bool isValidPath(std::pair<int, int>& coordinate) {
    return (coordinate.first >= 0 && coordinate.first < rowSize) &&
           (coordinate.second >= 0 && coordinate.second < colSize) && 
           (mazeData[coordinate.first][coordinate.second] == 'E' ||
            mazeData[coordinate.first][coordinate.second] == 'G');
  }

  bool isValidPath(Pair& coordinate) {
    return (coordinate.getPairX() >= 0 && coordinate.getPairX() < rowSize) &&
           (coordinate.getPairY() >= 0 && coordinate.getPairY() < colSize) && 
           (mazeData[coordinate.getPairX()][coordinate.getPairY()] == 'E' ||
            mazeData[coordinate.getPairX()][coordinate.getPairY()] == 'G');
  }



  // 根據stack路徑標記路徑 並避免G被蓋過
  void markPathToGoal(std::stack<std::pair<int, int>> pathStack,std::vector<std::pair<int, int>> goalCoord,  Maze& routeMaze) {
    routeMaze.setState(true);
    while (!pathStack.empty()) {
      std::pair<int, int> tempPair = pathStack.top();
      pathStack.pop();
      // 不是G才改為R
      if (!pairInVector(goalCoord, tempPair)) {
        routeMaze.setMazeSymbol(tempPair, 'R');
      }
    }
  }

  void solveMaze(int goldNum, Maze& routeMaze) {

    std::stack<std::pair<int, int>> pathStack;
    // 每個G的路徑
    std::vector<std::stack<std::pair<int, int>>> eachGoalPath;

    const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    bool findRouteToNGoal = false;
    
    int findGoalNum = 0;
    
    // start from (0,0)
    pathStack.push({0, 0});
    mazeData[0][0] = 'V';
    // 存已經找到的G座標
    std::vector<std::pair<int, int>> findGoalCoord;
    
    // stack不為空
    while(!pathStack.empty() && !findRouteToNGoal) {
      std::pair<int, int> tryCoordinate = pathStack.top(), curCoordinate = pathStack.top();

      bool canMoved = false;
      for (int i = 0; i < 4; i++) {
        // 根據上一步決定下一步方向
        int dirIndex = (lastStepDirection + i) % 4;
        std::pair<int, int> dir = directions[dirIndex];

        tryCoordinate = sumPair(curCoordinate, dir);
        
        // 先走還沒走過的路 沒超過邊界 是E或G
        if (isValidPath(tryCoordinate)) {
          // 先檢查到終點了嗎
          if (mazeData[tryCoordinate.first][tryCoordinate.second] == 'G') {
            // 如果此G還沒被找到過
            if (!pairInVector(findGoalCoord, tryCoordinate)) {
              // 代表找到目標 num++ 推入座標繼續找
              findGoalNum++;
              findGoalCoord.push_back(tryCoordinate);
              // 把此G的路徑座標推入vector ()
              eachGoalPath.push_back(pathStack);
              // 如果已經找到要求的數量 退出迴圈
              if (findGoalNum == goldNum) {
                // 下一個是G 也要將當前位置推入
                pathStack.push(tryCoordinate);
                findRouteToNGoal = true;
                break;
              }
              // 如果找到的是已經找過的G 即pop後繼續尋找
            } else {
              continue;
            }
            // 路線為E 可以走
          } else {
            // 更新為已訪問
            mazeData[tryCoordinate.first][tryCoordinate.second] = 'V';
          }
          // 座標推入堆疊
          pathStack.push(tryCoordinate);         
          canMoved = true;
          // 更新上一步的方向
          lastStepDirection = dirIndex;
          break;
        }
      }
      // 四個方向皆不能走 即回到上一步
      if (!canMoved) {
        pathStack.pop();
      }
    }
    // 如果成功找到路徑 即return state為true的routemaze 也就是已經標好的
    if (findRouteToNGoal) {
      routeMaze.setState(state);     
      // 到G的每個路徑都設為R
      for (int i = 0; i < eachGoalPath.size(); i++) {
        routeMaze.markPathToGoal(eachGoalPath[i], findGoalCoord, routeMaze);
      }
    }
  }

  int pathLength(std::stack<std::pair<int, int>> stack) {
    int path = 0;
    while (!stack.empty()) {
      stack.pop();
      path++;
    }
    return path;
  }
  //改
  void findShortsetPath(Maze& routeMaze) {
    Stack pathStack;
    // 每個G的路徑
    std::vector<Stack> eachGoalPath;

    Pair pair1(0, 1), pair2(1, 0), pair3(0, -1), pair4(-1, 0);

    const std::vector<Pair> directions = {pair1, pair2, pair3, pair4};
    // 標註有沒有答案
    bool findAPath = false;

    int curShortestLength = 10000;
    
    // start from (0,0)
    Pair pair(0, 0);
    pathStack.push(pair);
    mazeData[0][0] = 'V';
    // 存已經找到的G座標
    std::vector<Pair> findGoalCoord;
    
    // stack不為空
    while(!pathStack.empty()) {
      Pair tryCoordinate = pathStack.top(), curCoordinate = pathStack.top();

      bool canMoved = false;
      for (int i = 0; i < 4; i++) {
        // 根據上一步決定下一步方向
        int dirIndex = (lastStepDirection + i) % 4;
        Pair dir = directions[dirIndex];

        tryCoordinate = sumPair(curCoordinate, dir);
        
        // 先走還沒走過的路 沒超過邊界 是E或G
        if (isValidPath(tryCoordinate)) {
          // 先檢查到終點了嗎
          if (mazeData[tryCoordinate.getPairX()][tryCoordinate.getPairY()] == 'G') {
            findAPath = true;
            // 如果此G還沒被找到過
            if (!pairInVector(findGoalCoord, tryCoordinate)) {
              // 代表找到目標 num++ 推入座標繼續找

              findGoalCoord.push_back(tryCoordinate);
              // 把此G的路徑座標推入vector ()
              eachGoalPath.push_back(pathStack);
              // 如果找到的是已經找過的G 即pop後繼續尋找
            } else {
              continue;
            }
            // 路線為E 可以走
          } else {
            // 更新為已訪問
            mazeData[tryCoordinate.getPairX()][tryCoordinate.getPairY()] = 'V';
          }
          // 座標推入堆疊
          pathStack.push(tryCoordinate);         
          canMoved = true;
          // 更新上一步的方向
          lastStepDirection = dirIndex;
          break;
        }
      }
      // 四個方向皆不能走 即回到上一步
      if (!canMoved) {
        pathStack.pop();
      }
    }

    // 找完全部
    // if (findRouteToNGoal) {
    //   routeMaze.setState(state);     
    //   // 到G的每個路徑都設為R
    //   for (int i = 0; i < eachGoalPath.size(); i++) {
    //     routeMaze.markPathToGoal(eachGoalPath[i], findGoalCoord, routeMaze);
    //   }
    // }
  }

  void solveMazeShortestPathStack(Maze& routeMaze) {
    const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::stack<std::pair<int, int>> stack;
    std::stack<std::pair<int, int>> shortestPath;
    int shortestPathLength = 10000;
    bool findRouteToGoal = false; // 用於追蹤是否找到目標

    // 存已經找到的G座標
    std::vector<std::pair<int, int>> findGoalCoord;

    // 初始化起點
    stack.push({0, 0});
    mazeData[0][0] = 'V'; // 標記起點為已訪問

    while (!stack.empty()) {
        std::pair<int, int> cur = stack.top();

        bool moved = false;

        // 嘗試四個方向
        for (auto& dir : directions) {
            std::pair<int, int> next = {cur.first + dir.first, cur.second + dir.second};

            // 檢查是否為有效路徑
            if (isValidPath(next)) {
                stack.push(next); // 推入堆疊
                
                moved = true;

                // 如果找到目標點
                if (mazeData[next.first][next.second] == 'G') {

                  if (!pairInVector(findGoalCoord, next)) {
                    findGoalCoord.push_back(next);

                    findRouteToGoal = true;

                    
                  }
                  if (stack.size() < shortestPathLength) {
                    shortestPathLength = stack.size();
                    shortestPath = stack; // 更新最短路徑
                  }
                    
                } else {
                  mazeData[next.first][next.second] = 'V'; // 標記為已訪問
                }
                break;
            }
        }

        // 若無法移動，則回退
        if (!moved) {
            stack.pop(); // 將當前節點從堆疊移除
            if (!stack.empty()) {
                std::pair<int, int> back = stack.top();
                mazeData[back.first][back.second] = 'E'; // 恢復狀態
            }
        }
    }
  }
};


int main() {
  std::string command;
  int inputSize = 0;
  int goalNum;

  do {
    if (inputSize > 0) {
      command = command.substr(1);
      inputSize--;
    }
    std::cout << "*** Path Finding ***" << std::endl;
    std::cout << "* 0. Quit          *" << std::endl;
    std::cout << "* 1. One goal      *" << std::endl;
    std::cout << "* 2. More goals    *" << std::endl;
    std::cout << "* 3. Shortest path *" << std::endl;
    std::cout << "********************" << std::endl;

    std::cout << "Input a command(0, 1, 2, 3): ";
    Maze aMaze;

    if (inputSize == 0) {
      std::cin >> command;
      inputSize = command.size();
    }
    
    std::cout << std::endl;

    std::string fileName;

    if (command[0] == '1' || command[0] == '2' || command[0] == '3') {
      
      
      if (inputSize > 1) {
        // 不要command 只要fileName

        fileName = command.substr(1);
        //
        std::cout << "Input a file number: ";
        // 後面都當檔案名
        inputSize = 0;
      } else {
        
        std::cout << "Input a file number: ";
        std::cin >> fileName;
        inputSize--;
      }
            
      bool fileExist = false;
      checkFileNameExist(fileName, fileExist);

      //如果有此檔案才執行 沒有則跳出
      if (fileExist) {

        // 決定G數量
        if (command[0] == '1') goalNum = 1;
        else if (command[0] == '2') {
          goalNum = getNumber("Number of G (goals): ");
        } else {
          goalNum = -1;
        }
        
        if (aMaze.readMaze(fileName)) {

          Maze visitMaze(aMaze);
          Maze routeMaze(aMaze); 
          routeMaze.setState(false);
          // 任務三
          if (command[0] == 3) {
            visitMaze.solveMazeShortestPathStack(routeMaze);
            visitMaze.printMaze();

            std::cout << std::endl;
            // 任務一二
          } else {
            visitMaze.solveMaze(goalNum, routeMaze);  
            visitMaze.printMaze();
            std::cout << std::endl;
          }
          

          // 成功即印出路徑
          if (routeMaze.getState()) {
            routeMaze.printMaze();
            std::cout << std::endl;    
          }
          std::cout << std::endl;

          // 讀maze失敗  
        } else {
          std::cout << "read fail!";
        }

      } else {
        std::cout << std::endl << fileName << " does not exist!" << std::endl << std::endl;
        continue;
      }
    } else if (command[0] == '0') {
      break;
    } else {
      std::cout << "Command does not exist!" << std::endl << std::endl;
    }
  } while (true);

  return 0;
}
