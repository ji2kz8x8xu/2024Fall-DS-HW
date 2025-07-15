#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <cctype>
#include <iomanip>


#define MAXORDERNUM 3

bool isNumber(const std::string& str) {
  if (str.empty()) {
    return false; 
  }

  int start = 0;
  
  if (str[0] == '-') {
    if (str.length() == 1) {
      return false; 
    }
    start = 1; 
  }
    
  for (int i = start; i < str.length(); ++i) {
    if (!isdigit(static_cast<unsigned char>(str[i]))) {
       return false; 
    }
  }
  return true; 
}

// 檢查檔案是否存在
bool fileExist(std::string fileName) {
  std::ifstream file(fileName);

  return file.is_open();
}


class Order {
 private:
  int oId;
  int arrival;
  int duration;
  int timeOut;
 public:
  Order(int oId, int arrival, int duration, int timeOut) : oId(oId), arrival(arrival), duration(duration), timeOut(timeOut) {} 

  int getOId() {
    return oId;
  }

  int getArrival() {
    return arrival;
  }

  int getDuration() {
    return duration;
  }

  int getTimeOut() {
    return timeOut;
  }
};

class Queue {
 private:
  std::vector<Order> orderqueue;

 public:
  Queue() {}

  Queue(Queue& queue) {
    orderqueue = queue.getqueue();
  }

  std::vector<Order> getqueue() {
    return orderqueue;
  }

  bool isEmpty() {
    return orderqueue.size() == 0;
  }

  int getLength() {
    return orderqueue.size();
  }

  Order getFront() {
    return orderqueue.at(0);
  }

  void enqueue(int oId, int arrival, int duration, int timeOut) {
    Order aOrder(oId, arrival, duration, timeOut);
    orderqueue.push_back(aOrder);
  }

  void enqueue(Order aOrder) {
    orderqueue.push_back(aOrder);
  }

  Order dequeue() {
    if (isEmpty()) {
      std::cout << "empty queue." << std::endl;
    } else {
      Order queueFront = orderqueue.at(0);
      orderqueue.erase(orderqueue.begin());
      return queueFront;
    }
  }

  void readFromFile(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string line;

    // 先去掉第一行
    getline(inputFile, line);

    while (getline(inputFile, line)) {
      std::istringstream iss(line);
      std::string data;
      int dataCount = 0, oId, arr, dur, out;
      while (getline(iss, data, '\t')) {
        switch (dataCount) {
          case 0:
            oId = stoi(data);
            break;
          case 1:
            arr = stoi(data);
            break;
          case 2:
            dur = stoi(data);
            break;
          case 3:
            out = stoi(data);
            break;
          default:
            break;
        }
        dataCount++;
      }
      enqueue(oId, arr, dur, out);
    }
    inputFile.close();
  }

  void writeToFile(std::string fileName) {
    std::ofstream outputFile(fileName);

    outputFile << "OID	Arrival	Duration	TimeOut" << std::endl;
    if (!isEmpty()) {
      for (int i = 0; i < orderqueue.size(); i++) {
        outputFile << orderqueue.at(i).getOId() << '\t' << orderqueue.at(i).getArrival() << '\t' 
                   << orderqueue.at(i).getDuration() << '\t' << orderqueue.at(i).getTimeOut() << std::endl;
      }
    } else {
      std::cout << "empty queue!!" << std::endl;
    }
    outputFile.close();
  }

  void shellSort() {
    int n = getLength();

    // Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2) {
      for (int i = gap; i < n; i++) {
        Order temp = orderqueue[i];
        int j;
        for (j = i; j >= gap; j -= gap) {
          if (orderqueue[j - gap].getArrival() > temp.getArrival() || 
              (orderqueue[j - gap].getArrival() == temp.getArrival() &&
              orderqueue[j - gap].getOId() > temp.getOId())) {
            orderqueue[j] = orderqueue[j - gap];
          } else {
            break;
          }
        }
        orderqueue[j] = temp;
      }
    }
  }
};

class List {
 private:
  int oId;
  int cId;
  int delayTime;
  int actionTime;
 public:
  List(int oId, int cId, int delayTime, int actionTime) : oId(oId), cId(cId), delayTime(delayTime), actionTime(actionTime) {}
  List(int oId, int delayTime, int actionTime) : oId(oId), cId(-1), delayTime(delayTime), actionTime(actionTime) {}
  
  int getOId() {
    return oId;
  }

  int getCId() {
    return cId;
  }
  
  int getDelayTime() {
    return delayTime;
  }
  
  int getActionTime() {
    return actionTime;
  }
};

class ListManage {
 private:
  std::vector<List> abortList;
  std::vector<List> timeOutList;
  // 任務二 無cid:-1  任務三 無cid:0
  int mode;
 public:
  ListManage() : mode(-1) {}
  ListManage(int mode) : mode(mode) {}
  void addAbortList(List& list) {
    abortList.push_back(list);
  }
  void addTimeOutList(List& list) {
    timeOutList.push_back(list);
  }
  int getTotalNum() {
    return abortList.size() + timeOutList.size();
  }

  void writeToFile(std::string fileName, int orderNum) {
    std::ofstream outputFile(fileName);
    int totalDelay = 0;
    if (mode == -1) {
      outputFile << '\t' << "[Abort List]" << std::endl;
      outputFile << '\t' << "OID" << '\t' << "Delay"<< '\t' << "Abort" << std::endl;

      for (int i = 0; i < abortList.size(); i++) {
        totalDelay += abortList.at(i).getDelayTime();
        outputFile << "[" << i + 1 << "]" << '\t' << abortList.at(i).getOId() << '\t' 
                  << abortList.at(i).getDelayTime() << '\t' << abortList.at(i).getActionTime() << std::endl;
      }

      outputFile << '\t' << "[Timeout List]" << std::endl;
      outputFile << '\t' << "OID" << '\t' << "Delay" << '\t' << "Departure" << std::endl;

      for (int i = 0; i < timeOutList.size(); i++) {
        totalDelay += timeOutList.at(i).getDelayTime();
        outputFile << "[" << i + 1 << "]" << '\t' << timeOutList.at(i).getOId() << '\t' 
                  << timeOutList.at(i).getDelayTime() << '\t' << timeOutList.at(i).getActionTime() << std::endl;
      }

      outputFile <<  "[Total Delay]" << std::endl;
      outputFile << totalDelay << " min." << std::endl;
      outputFile <<  "[Failure Percentage]" << std::endl;
      outputFile << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(getTotalNum()) / static_cast<double>(orderNum) << " %" << std::endl;
      outputFile.close();
    } else if (mode == 0) {
      outputFile << '\t' << "[Abort List]" << std::endl;
      outputFile << '\t' << "OID" << '\t' << "CID" << '\t' << "Delay"<< '\t' << "Abort" << std::endl;

      for (int i = 0; i < abortList.size(); i++) {
        totalDelay += abortList.at(i).getDelayTime();
        outputFile << "[" << i + 1 << "]" << '\t' << abortList.at(i).getOId() << '\t' << abortList.at(i).getCId() << '\t' 
                  << abortList.at(i).getDelayTime() << '\t' << abortList.at(i).getActionTime() << std::endl;
      }

      outputFile << '\t' << "[Timeout List]" << std::endl;
      outputFile << '\t' << "OID" << '\t' << "CID" << '\t' << "Delay" << '\t' << "Departure" << std::endl;

      for (int i = 0; i < timeOutList.size(); i++) {
        totalDelay += timeOutList.at(i).getDelayTime();
        outputFile << "[" << i + 1 << "]" << '\t' << timeOutList.at(i).getOId() << '\t' << abortList.at(i).getCId() << '\t' 
                  << timeOutList.at(i).getDelayTime() << '\t' << timeOutList.at(i).getActionTime() << std::endl;
      }

      outputFile <<  "[Total Delay]" << std::endl;
      outputFile << totalDelay << " min." << std::endl;
      outputFile <<  "[Failure Percentage]" << std::endl;
      outputFile << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(getTotalNum()) / static_cast<double>(orderNum) << " %" << std::endl;
      outputFile.close();
    }
    
  }
  void printContent() {
    std::cout << "abortList";
    for (int i = 0; i < abortList.size(); i++) {
      std::cout << abortList.at(i).getOId() << " ";
    }
    for (int i = 0; i < timeOutList.size(); i++) {
      std::cout << timeOutList.at(i).getOId() << " ";
    }
  }
};


int main() {
  
  while (1) {
    std::string command, fileName;

    Queue orderQueue;

    std::cout << "**** Simulate FIFO Queues by SQF *****" << std::endl;
    std::cout << "* 0. Quit                            *" << std::endl;
    std::cout << "* 1. Sort a file                     *" << std::endl;
    std::cout << "* 2. Simulate one FIFO queue         *" << std::endl;
    std::cout << "* 3. Simulate two queues by SQF      *" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "Input a command(0, 1, 2, 3): ";

    std::cin >> command;
    std::cout << std::endl;

    if (!isNumber(command)) {
      break;
    }

    if (command != "0" && command != "1" && command != "2" && command != "3") {
      std::cout << "Command does not exist!" << std::endl << std::endl;
      continue;
    }
    
    else if (command == "0") break;
    else if (command == "1" || command == "2" || command == "3") {
      std::cout << "Input a file number (e.g., 401, 402, 403, ...): ";
      std::cin >> fileName;
      std::cout << std::endl;

      if (command == "1") {

        if (!fileExist("input" + fileName + ".txt")) {
          std::cout << "### input" << fileName << ".txt does not exist! ###" << std::endl << std::endl;
          continue;
        }

        auto readStartTime = std::chrono::high_resolution_clock::now();
        clock_t readStartClock = clock(); 

        orderQueue.readFromFile("input" + fileName + ".txt");
        
        auto readEndTime = std::chrono::high_resolution_clock::now();
        clock_t readEndClock = clock(); 
        std::chrono::duration<double, std::milli> readDuration = readEndTime - readStartTime;

        // ----------------

        auto sortStartTime = std::chrono::high_resolution_clock::now();
        clock_t sortStartClock = clock(); 
        
        orderQueue.shellSort();

        auto sortEndTime = std::chrono::high_resolution_clock::now();
        clock_t sortEndClock = clock(); 
        std::chrono::duration<double, std::milli> sortDuration = sortEndTime - sortStartTime;
        // --------------------

        Queue copyQueue(orderQueue);

        auto writeStartTime = std::chrono::high_resolution_clock::now();
        clock_t writeStartClock = clock(); 

        copyQueue.writeToFile("sorted" + fileName + ".txt");

        auto writeEndTime = std::chrono::high_resolution_clock::now();
        clock_t writeEndClock = clock(); 
        std::chrono::duration<double, std::milli> writeDuration = writeEndTime - writeStartTime;
        
        std::cout << "Reading data: " << readEndClock - readStartClock << " clocks " << "(";
        std::cout << std::fixed << std::setprecision(2) << readDuration.count() << " ms)." << std::endl << std::endl;
        std::cout << "Sorting data: " << sortEndClock - sortStartClock << " clocks " << "(";
        std::cout << std::fixed << std::setprecision(2) << sortDuration.count() << " ms)." << std::endl << std::endl;
        std::cout << "Writing data: " << writeEndClock - writeStartClock << " clocks " << "(";
        std::cout << std::fixed << std::setprecision(2) << writeDuration.count() << " ms)." << std::endl << std::endl;


      } else if (command == "2") {

        if (!fileExist("sorted" + fileName + ".txt")) {
          std::cout << "### sorted" << fileName << ".txt does not exist! ###" << std::endl << std::endl;
          continue;
        }

        Queue chefQueue, noOkOrderQueue, orderQueue;
        ListManage listManage(-1);
        
        noOkOrderQueue.readFromFile("sorted" + fileName + ".txt");
        noOkOrderQueue.shellSort();

        
        //去除 Duration=0和arrival+duration>timeout之訂單
        while (1) {
          Order tempOrder = noOkOrderQueue.dequeue();
          if (tempOrder.getDuration() == 0 || tempOrder.getArrival() + tempOrder.getDuration() > tempOrder.getTimeOut()) {
            continue;
          }
          orderQueue.enqueue(tempOrder);
          if (noOkOrderQueue.isEmpty()) break;
        }

        int orderNum = orderQueue.getLength();

        int nowTime = 0;
        int preTime = 0;
        while (1) {

          // 將訂單放入chefQueue
          while (chefQueue.getLength() < MAXORDERNUM + 1 && orderQueue.getLength() > 0) {          
            chefQueue.enqueue(orderQueue.dequeue());
          }

          // 處理chefQueue的abort list
          if (nowTime >= chefQueue.getFront().getTimeOut()) {
            Order tempOrder = chefQueue.dequeue();
            int oId = tempOrder.getOId();
            int delay = nowTime - tempOrder.getArrival();
            int abort = nowTime;
            List list(oId, delay, abort);
            listManage.addAbortList(list);
          } else if (nowTime < chefQueue.getFront().getArrival()) {
            nowTime = chefQueue.getFront().getArrival();
          } else {
            preTime = nowTime;
            nowTime = nowTime + chefQueue.getFront().getDuration();
            // time out list
            if (nowTime > chefQueue.getFront().getTimeOut()) {
              Order tempOrder = chefQueue.getFront();
              int oId = tempOrder.getOId();
              int delay = preTime - tempOrder.getArrival();
              int departure = nowTime;
              List list(oId, delay, departure);
              listManage.addTimeOutList(list);
            }
            chefQueue.dequeue();
          }

          while (!orderQueue.isEmpty()) {
            if (nowTime > orderQueue.getFront().getArrival()) {
              Order tempOrder = orderQueue.dequeue();
              int oId = tempOrder.getOId();
              int delay = 0;
              int abort = tempOrder.getArrival();
              List list(oId, delay, abort);
              listManage.addAbortList(list);
            } else break;
          }
          if (chefQueue.isEmpty()) break;
        }
        listManage.writeToFile("output" + fileName + ".txt", orderNum);
      } else if (command == "3") {
        if (!fileExist("sorted" + fileName + ".txt")) {
          std::cout << "### sorted" << fileName << ".txt does not exist! ###" << std::endl << std::endl;
          continue;
        }

        Queue chefQueue1, chefQueue2, noOkOrderQueue, orderQueue;
        ListManage listManage(0);
        
        noOkOrderQueue.readFromFile("sorted" + fileName + ".txt");
        noOkOrderQueue.shellSort();

        //去除 Duration=0和arrival+duration>timeout之訂單
        while (1) {
          Order tempOrder = noOkOrderQueue.dequeue();
          if (tempOrder.getDuration() == 0 || tempOrder.getArrival() + tempOrder.getDuration() > tempOrder.getTimeOut()) {
            continue;
          }
          orderQueue.enqueue(tempOrder);
          if (noOkOrderQueue.isEmpty()) break;
        }

        int orderNum = orderQueue.getLength();

        int nowTime1 = 0;
        int preTime1 = 0;
        int nowTime2 = 0;
        int preTime2 = 0;
        int curTime = 0;
        while (1) {

          // 將訂單放入chefQueue
          while ((chefQueue1.getLength() < MAXORDERNUM + 1 || chefQueue2.getLength() < MAXORDERNUM + 1) && orderQueue.getLength() > 0) {          
            if (chefQueue1.getLength() <= chefQueue2.getLength()) {
              chefQueue1.enqueue(orderQueue.dequeue());
            } else {
              chefQueue2.enqueue(orderQueue.dequeue());
            }                    
          }

          bool chef1Empty = (chefQueue1.getLength() == 0) ? 1 : 0;
          bool chef2Empty = (chefQueue2.getLength() == 0) ? 1 : 0;
          
          if (!chef1Empty && !chef2Empty && chefQueue1.getFront().getArrival() <= chefQueue2.getFront().getArrival()) {
            // 處理chefQueue的abort list
            if (nowTime1 >= chefQueue1.getFront().getTimeOut()) {
              Order tempOrder = chefQueue1.dequeue();
              int oId = tempOrder.getOId();
              int delay = nowTime1 - tempOrder.getArrival();
              int abort = nowTime1;
              List list(oId, delay, abort);
              listManage.addAbortList(list);
            } else if (nowTime1 < chefQueue1.getFront().getArrival()) {
              nowTime1 = chefQueue1.getFront().getArrival();
              
            } else {
              preTime1 = nowTime1;
              nowTime1 = nowTime1 + chefQueue1.getFront().getDuration();
              // time out list
              if (nowTime1 > chefQueue1.getFront().getTimeOut()) {
                Order tempOrder = chefQueue1.getFront();
                int oId = tempOrder.getOId();
                int delay = preTime1 - tempOrder.getArrival();
                int departure = nowTime1;
                List list(oId, delay, departure);
                listManage.addTimeOutList(list);
              }
              chefQueue1.dequeue();
            }
          } else if (!chef1Empty && !chef2Empty && chefQueue1.getFront().getArrival() > chefQueue2.getFront().getArrival()) {
            if (nowTime2 >= chefQueue2.getFront().getTimeOut()) {
              Order tempOrder = chefQueue2.dequeue();
              int oId = tempOrder.getOId();
              int delay = nowTime2 - tempOrder.getArrival();
              int abort = nowTime2;
              List list(oId, delay, abort);
              listManage.addAbortList(list);
            } else if (nowTime2 < chefQueue2.getFront().getArrival()) {
              nowTime2 = chefQueue2.getFront().getArrival();
            } else {
              preTime2 = nowTime2;
              nowTime2 = nowTime2 + chefQueue2.getFront().getDuration();
              // time out list
              if (nowTime2 > chefQueue2.getFront().getTimeOut()) {
                Order tempOrder = chefQueue2.getFront();
                int oId = tempOrder.getOId();
                int delay = preTime2 - tempOrder.getArrival();
                int departure = nowTime2;
                List list(oId, delay, departure);
                listManage.addTimeOutList(list);
              }
              chefQueue2.dequeue();
            }
          } else if (!chef1Empty && chef2Empty) {
            // 處理chefQueue的abort list
            if (nowTime1 >= chefQueue1.getFront().getTimeOut()) {
              Order tempOrder = chefQueue1.dequeue();
              int oId = tempOrder.getOId();
              int delay = nowTime1 - tempOrder.getArrival();
              int abort = nowTime1;
              List list(oId, delay, abort);
              listManage.addAbortList(list);
            } else if (nowTime1 < chefQueue1.getFront().getArrival()) {
              nowTime1 = chefQueue2.getFront().getArrival();
            } else {
              preTime1 = nowTime1;
              nowTime1 = nowTime1 + chefQueue1.getFront().getDuration();
              // time out list
              if (nowTime1 > chefQueue1.getFront().getTimeOut()) {
                Order tempOrder = chefQueue1.getFront();
                int oId = tempOrder.getOId();
                int delay = preTime1 - tempOrder.getArrival();
                int departure = nowTime1;
                List list(oId, delay, departure);
                listManage.addTimeOutList(list);
              }
              chefQueue1.dequeue();
            }
          } else if (!chef2Empty && chef1Empty) {
            // 處理chefQueue的abort list
            if (nowTime2 >= chefQueue2.getFront().getTimeOut()) {
              Order tempOrder = chefQueue2.dequeue();
              int oId = tempOrder.getOId();
              int delay = nowTime2 - tempOrder.getArrival();
              int abort = nowTime2;
              List list(oId, delay, abort);
              listManage.addAbortList(list);
            } else if (nowTime2 < chefQueue2.getFront().getArrival()) {
              nowTime2 = chefQueue2.getFront().getArrival();
            } else {
              preTime2 = nowTime2;
              nowTime2 = nowTime2 + chefQueue2.getFront().getDuration();
              // time out list
              if (nowTime2 > chefQueue2.getFront().getTimeOut()) {
                Order tempOrder = chefQueue2.getFront();
                int oId = tempOrder.getOId();
                int delay = preTime2 - tempOrder.getArrival();
                int departure = nowTime2;
                List list(oId, delay, departure);
                listManage.addTimeOutList(list);
              }
              chefQueue2.dequeue();
            }
          }
          if (nowTime1 > nowTime2) {
            curTime = nowTime1;
          } else {
            curTime = nowTime2;
          }
          
          // // 處理chefQueue的abort list
          // if (nowTime >= chefQueue.getFront().getTimeOut()) {
          //   Order tempOrder = chefQueue.dequeue();
          //   int oId = tempOrder.getOId();
          //   int delay = nowTime - tempOrder.getArrival();
          //   int abort = nowTime;
          //   List list(oId, delay, abort);
          //   listManage.addAbortList(list);
          // } else if (nowTime < chefQueue.getFront().getArrival()) {
          //   nowTime = chefQueue.getFront().getArrival();
          // } else {
          //   preTime = nowTime;
          //   nowTime = nowTime + chefQueue.getFront().getDuration();
          //   // time out list
          //   if (nowTime > chefQueue.getFront().getTimeOut()) {
          //     Order tempOrder = chefQueue.getFront();
          //     int oId = tempOrder.getOId();
          //     int delay = preTime - tempOrder.getArrival();
          //     int departure = nowTime;
          //     List list(oId, delay, departure);
          //     listManage.addTimeOutList(list);
          //   }
          //   chefQueue.dequeue();
          // }

          while (!orderQueue.isEmpty()) {
            if (curTime > orderQueue.getFront().getArrival()) {
              Order tempOrder = orderQueue.dequeue();
              int oId = tempOrder.getOId();
              int delay = 0;
              int abort = tempOrder.getArrival();
              List list(oId, delay, abort);
              listManage.addAbortList(list);
            } else break;
          }
          if (chefQueue1.isEmpty() && chefQueue2.isEmpty()) break;
        }
        listManage.writeToFile("cooks" + fileName + ".txt", orderNum);


      }
    }
  }
  return 0;
}

