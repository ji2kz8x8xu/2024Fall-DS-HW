#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <unordered_map>

// 檢查檔案是否存在
bool fileExist(std::string prefix, std::string fileName) {
  std::string fileFullName = prefix + fileName + ".txt";
  std::ifstream File(fileFullName);
  if (!File) {
    return false;
  }
  return true;
}


// get exist file name, return file name
// 獲取存在的檔案名稱，不斷輸入直到為有效檔名為止
std::string getExistFileName(std::string prefix) {
  std::string fileName;
  while (1) {
    std::cin >> fileName;
    if (fileExist(prefix, fileName)) { 
      break;
    } else if (fileName == "0") {
      break;
    } else {
      fileName = prefix + fileName;
      std::cout  << std::endl << "### " << fileName << ".txt does not exist! ###" << std::endl;
      std::cout  << std::endl << "Input 201, 202, ...[0]Quit): ";
    }
  }
  return fileName;
}

// 檢查字串是否為有效的數字
bool isValidNumber(const std::string& str) {
    if (str.empty()) return false;
    
    // 檢查第一個字元是不是負號
    int start = 0;
    if (str[0] == '-') {
        start = 1;
        if (str.length() == 1) return false; // 只有負號，不是數字
    }

    // 檢查剩下的字元是否都是數字
    for (int i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
// 一直取直到為合法數字
int getNumber(std::string msg) {
    std::string input;
    int num;
    // 小於0在輸一次 大於9999 輸出不在範圍[0,9999] 不是數字 在輸一次
    while (true) {
        std::cout << msg;
        std::cin >> input;
        std::cout << std::endl;
        // 檢查是否為有效的數字
        if (isValidNumber(input)) {
            // 將字串轉換為整數
            num = stoi(input);

            // 檢查數字是否在範圍內
            if (num >= 0 && num <= 9999) {
                return num;
              // 數字大於9999 顯示錯誤資訊
            } else if (num > 9999) {
              std::cout << "### It is NOT in [0,9999] ###" << std::endl << std::endl;
              // 數字小於0 繼續輸入
            } else continue;
          // 非數字 繼續輸入  
        } else continue;
        
    }
}

// 學生資訊類別
class studentInfo {
 private:
  std::string schoolCode;         // 學校代碼
  std::string schoolName;         // 學校名稱
  std::string departmentCode;     // 科系代碼
  std::string departmentName;     // 科系名稱
  std::string dayEveningDivision; // 日間/進修別
  std::string level;              // 等級別
  std::string numberOfStudents;   // 學生數
  std::string numberOfTeachers;   // 教師數
  std::string numberOfGraduates;  // 上學年度畢業生數
  std::string countyCityName;     // 縣市名稱
  std::string systemType;         // 體系別
 public:
  // constructor 初始化各項資料
  studentInfo() {
    schoolCode = "N/A"; 
    schoolName = "Unknown"; 
    departmentCode = "N/A";
    departmentName = "N/A";
    dayEveningDivision = "Day";
    level = "N/A";
    numberOfStudents = "0";
    numberOfTeachers = "0";
    numberOfGraduates = "0";
    countyCityName = "Unknown";
    systemType = "N/A";
  }

  // Setter method
  void setSchoolCode(const std::string& code) {
    schoolCode = code;
  }

  void setSchoolName(const std::string& name) {
    schoolName = name;
  }

  void setDepartmentCode(const std::string& code) {
    departmentCode = code;
  }

  void setDepartmentName(const std::string& name) {
    departmentName = name;
  }

  void setDayEveningDivision(const std::string& division) {
    dayEveningDivision = division;
  }

  void setLevel(const std::string& lvl) {
    level = lvl;
  }

  void setNumberOfStudents(const std::string& num) {
    numberOfStudents = num;
  }

  void setNumberOfTeachers(const std::string& num) {
    numberOfTeachers = num;
  }

  void setNumberOfGraduates(const std::string& num) {
    numberOfGraduates = num;
  }

  void setCountyCityName(const std::string& name) {
    countyCityName = name;
  }

  void setSystemType(const std::string& type) {
    systemType = type;
  }

  // Getter method
  const std::string& getSchoolCode() const {
    return schoolCode;
  }

  const std::string& getSchoolName() const {
    return schoolName;
  }

  const std::string& getDepartmentCode() const {
    return departmentCode;
  }

  const std::string& getDepartmentName() const {
    return departmentName;
  }

  const std::string& getDayEveningDivision() const {
    return dayEveningDivision;
  }

  const std::string& getLevel() const {
    return level;
  }

  const std::string& getNumberOfStudents() const {
    return numberOfStudents;
  }

  const std::string& getNumberOfTeachers() const {
    return numberOfTeachers;
  }

  const std::string& getNumberOfGraduates() const {
    return numberOfGraduates;
  }

  const std::string& getCountyCityName() const {
    return countyCityName;
  }

  const std::string& getSystemType() const {
    return systemType;
  }
};

// 文件數據操作類別
class fileData {
 private:
 // 用 vector 設置 studentInfo 物件列表
  std::vector<studentInfo> totalFileData;
  // 根據欄位索引設置學生資訊的內容
  void set_data(int dataCount, const std::string& data, const int infoCount) {
    switch (dataCount) {
      case 0:
        totalFileData.at(infoCount).setSchoolCode(data);
        break;
      case 1:
        totalFileData.at(infoCount).setSchoolName(data);
        break;
      case 2:
        totalFileData.at(infoCount).setDepartmentCode(data); 
        break;
      case 3:
        totalFileData.at(infoCount).setDepartmentName(data);
        break;
      case 4:
        totalFileData.at(infoCount).setDayEveningDivision(data);
        break;
      case 5:
        totalFileData.at(infoCount).setLevel(data);
        break;
      case 6:
        totalFileData.at(infoCount).setNumberOfStudents(data);
        break;
      case 7:
        totalFileData.at(infoCount).setNumberOfTeachers(data);
        break;
      case 8:
        totalFileData.at(infoCount).setNumberOfGraduates(data);
        break;
      case 9:
        totalFileData.at(infoCount).setCountyCityName(data);
        break;
      case 10:
        totalFileData.at(infoCount).setSystemType(data);
        break;
      default:
        break;
    }
  }
 public:
  void setFileData(const std::vector<studentInfo>& fileData) {
    totalFileData = fileData;
  }

  // return記錄的數量
  int getSize() {
    return totalFileData.size();
  }

  // 從檔案讀資料放到fileData
  void readFromFile(std::string fileName, bool removeHeader) {
    std::string inputFileName = fileName;
    std::ifstream inputFile(inputFileName);

    // 去掉第一行
    std::string line;
    if (removeHeader) {
      std::getline(inputFile, line);
    }

    int infoCount = 0;
    while (std::getline(inputFile, line)) {
      studentInfo studentInfo;
      totalFileData.push_back(studentInfo);

      std::istringstream iss(line);
      std::string data;
      int dataCount = 0;

      while (getline(iss, data, '\t')) {
        set_data(dataCount, data, infoCount);
        dataCount++;
      }
      infoCount++;
    }
    inputFile.close();
  }
  
  void writeToFile(std::string fileName) {
    std::ofstream outputFile(fileName + ".txt");
    
    for (int i = 0; i < totalFileData.size(); i++) {
      outputFile << totalFileData.at(i).getSchoolCode() << "\t"
                 << totalFileData.at(i).getSchoolName() << "\t"
                 << totalFileData.at(i).getDepartmentCode() << "\t"
                 << totalFileData.at(i).getDepartmentName() << "\t"
                 << totalFileData.at(i).getDayEveningDivision() << "\t"
                 << totalFileData.at(i).getLevel() << "\t"
                 << totalFileData.at(i).getNumberOfStudents() << "\t"
                 << totalFileData.at(i).getNumberOfTeachers() << "\t"
                 << totalFileData.at(i).getNumberOfGraduates() << "\t"
                 << totalFileData.at(i).getCountyCityName() << "\t"
                 << totalFileData.at(i).getSystemType() << std::endl;
    }
    outputFile.close();
  }

  // 輸出所有記錄
  void printOutAll() {
    if (totalFileData.size() == 0) {
      std::cout << "File Empty!!" << std::endl;
    } else {
      std::cout << "schoolCode schoolName departmentCode departmentName ";
      std::cout << "dayEveningDivision level numberOfStudents numberOfTeachers  ";
      std::cout << "numberOfGraduates countyCityName systemType" << std::endl;
      for (int i = 0; i < totalFileData.size(); i++) {
        std::cout << totalFileData.at(i).getSchoolCode() << "  "
                  << totalFileData.at(i).getSchoolName() << "  "
                  << totalFileData.at(i).getDepartmentCode() << "  "
                  << totalFileData.at(i).getDepartmentName() << "  "
                  << totalFileData.at(i).getDayEveningDivision() << "  " 
                  << totalFileData.at(i).getLevel() << "  "           
                  << totalFileData.at(i).getNumberOfStudents() << "  " 
                  << totalFileData.at(i).getNumberOfTeachers() << "  " 
                  << totalFileData.at(i).getNumberOfGraduates() << "  "
                  << totalFileData.at(i).getCountyCityName() << "  "   
                  << totalFileData.at(i).getSystemType() << std::endl;
      }
    }
  }
  // 根據最少的學生和畢業生數量過濾記錄(留下符合資格的)
  fileData filterFile(int studentsNum, int graduatesNum) {
    std::vector<studentInfo> afterFilter;

    for (int i = 0; i < totalFileData.size(); i++) {
      bool qualified1 = false, qualified2 = false;
      int myStudentsNum = stoi(totalFileData.at(i).getNumberOfStudents());
      int myGraduatesNum = stoi(totalFileData.at(i).getNumberOfGraduates());

      if (myStudentsNum >= studentsNum) {
        qualified1 = true;
      }
      if (myGraduatesNum >= graduatesNum) {
        qualified2 = true; 
      }
      if (qualified1 && qualified2) {
        studentInfo stu;
        stu.setSchoolCode(totalFileData.at(i).getSchoolCode());
        stu.setSchoolName(totalFileData.at(i).getSchoolName());
        stu.setDepartmentCode(totalFileData.at(i).getDepartmentCode());
        stu.setDepartmentName(totalFileData.at(i).getDepartmentName());
        stu.setDayEveningDivision(totalFileData.at(i).getDayEveningDivision());
        stu.setLevel(totalFileData.at(i).getLevel());
        stu.setNumberOfStudents(totalFileData.at(i).getNumberOfStudents());
        stu.setNumberOfTeachers(totalFileData.at(i).getNumberOfTeachers());
        stu.setNumberOfGraduates(totalFileData.at(i).getNumberOfGraduates());
        stu.setCountyCityName(totalFileData.at(i).getCountyCityName());
        stu.setSystemType(totalFileData.at(i).getSystemType());
        afterFilter.push_back(stu);
      }
    }
    fileData fileData;
    fileData.setFileData(afterFilter);
    return fileData;
  }
  // merge with other file
  fileData mergeWith(const fileData& other) {
    std::vector<studentInfo> merged = totalFileData, temp;

    for (int i = 0; i < other.totalFileData.size(); i++) {
      for (int j = merged.size() - 1; j >= 0 ; j--) {  
        
        // 學校代碼一樣 校系代碼一樣 系所名稱一樣
        if (other.totalFileData.at(i).getSchoolCode() == merged.at(j).getSchoolCode() && 
            other.totalFileData.at(i).getDepartmentCode() == merged.at(j).getDepartmentCode() &&
            other.totalFileData.at(i).getDepartmentName() == merged.at(j).getDepartmentName()) {
          // studentInfo
          merged.insert(merged.begin() + j + 1, other.totalFileData.at(i));
          break;
          
        }
        if (j == 0) {
          temp.push_back(other.totalFileData.at(i));
        }
      }  
    }
    // temp放merged後面
    merged.insert(merged.end(), temp.begin(), temp.end());

    fileData file;
    file.setFileData(merged);
    return file;
  }
  // fileData mergeWith(const fileData& other) {
  //   std::vector<studentInfo> merged = totalFileData, temp;

  //   for (int i = 0; i < other.totalFileData.size(); i++) {
  //     for (int j = 0; j < merged.size() ; j++) {   
  //       // 學校代碼一樣
  //       if (other.totalFileData.at(i).getSchoolCode() == merged.at(j).getSchoolCode()) {
  //         // 校系代碼一樣
  //         if (other.totalFileData.at(i).getDepartmentCode() == merged.at(j).getDepartmentCode()) {
  //           // 系所名稱一樣
  //           if (other.totalFileData.at(i).getDepartmentName() == merged.at(j).getDepartmentName()) {
  //             if (other.totalFileData.size() < i + 1 && 
  //                 other.totalFileData.at(i).getDepartmentName() != other.totalFileData.at(i + 1).getDepartmentName() &&
  //                 other.totalFileData.size() < i + 2 &&
  //                 other.totalFileData.at(i).getDepartmentName() != other.totalFileData.at(i + 2).getDepartmentName() &&
  //                 other.totalFileData.size() < i + 3 &&
  //                 other.totalFileData.at(i).getDepartmentName() != other.totalFileData.at(i + 3).getDepartmentName() ) {
  //               merged.insert(merged.begin() + j + 2, other.totalFileData.at(i));
  //               break;
                
  //             }
  //           }
  //         }
  //       }
  //       if (j == merged.size() - 1) {
  //         temp.push_back(other.totalFileData.at(i));
  //       }
  //     }  
  //   }
  //   // temp放merged後面
  //   merged.insert(merged.end(), temp.begin(), temp.end());

  //   fileData file;
  //   file.setFileData(merged);
  //   return file;
  // }
};

int main() {

  int choice = 0;
  int command = -1;
  
  while (1) {
    std::cout << "***  File Object Manipulator  ***" << std::endl;
    std::cout << "* 0. QUIT                       *" << std::endl;
    std::cout << "* 1. COPY (Read & Save a file)  *" << std::endl;
    std::cout << "* 2. FILTER (Reduce a file)     *" << std::endl;
    std::cout << "* 3. MERGE (Join two files)     *" << std::endl;
    std::cout << "* 4. MERGE (Join M files)   *" << std::endl;
    std::cout << "*********************************" << std::endl;


    std::cout << "Input a choice(0, 1, 2, 3, 4): ";
    std::cin >> choice;
    command = choice;
    std::cout << std::endl;

    if (command == 0) break;
    // 任務一
    else if (command == 1) {
      fileData fileData;
      std::string fileName;
      std::cout << "Input 201, 202, ...[0]Quit): ";
      fileName = getExistFileName("input");
      if (fileName != "0") {
        std::cout << std::endl;
        fileData.readFromFile("input" + fileName+ ".txt", true);
        fileData.writeToFile("copy" + fileName);
        std::cout << "Number of records = " << fileData.getSize() << std::endl;
      }
      // 任務二
    } else if (command == 2) {
      fileData fileData, afterFilterFile;
      std::string fileName;
      std::cout << "Input 201, 202, ...[0]Quit): ";
      fileName = getExistFileName("copy");
      fileData.readFromFile("copy" + fileName + ".txt", false);
      if (fileData.getSize() != 0) {
        std::cout << std::endl;
        int studentsNum, graduatesNum;
        studentsNum = getNumber("Input a lower bound on the number of students: ");
        graduatesNum = getNumber("Input a lower bound on the number of graduates: ");
        afterFilterFile = fileData.filterFile(studentsNum, graduatesNum);
        afterFilterFile.writeToFile("copy" + fileName);
        std::cout << "Number of records = " << afterFilterFile.getSize() << std::endl;
      }
      // 任務三
    } else if (command == 3) {
      fileData file, targetFile, afterMergeFile;
      std::string fileName, targetFileName;
      std::cout << "Input 201, 202, ...[0]Quit): ";
      fileName = getExistFileName("copy");
      if (fileName != "0") {
        file.readFromFile("copy" + fileName + ".txt", false);
        std::cout << std::endl;
        std::cout << "Input 201, 202, ...[0]Quit): ";
        targetFileName = getExistFileName("copy");
        if (targetFileName != "0") {
          targetFile.readFromFile("copy" + targetFileName + ".txt", false);
          std::cout << std::endl;
          afterMergeFile = file.mergeWith(targetFile);
          std::string outputFileName = "output" + fileName + "_" + targetFileName + ".txt";
          afterMergeFile.writeToFile(outputFileName);
          std::cout << "Number of records = " << afterMergeFile.getSize() << std::endl;
        }
      }
      // 任務四
    } else if (command == 4) {
      fileData file;
      std::string fileName, targetFileName;
      std::cout << "Input 201, 202, ...[0]Quit): ";
      fileName = getExistFileName("copy");

      if (fileName != "0") {
        std::cout << std::endl;
        file.readFromFile("copy" + fileName + ".txt", false);
        std::string outputFileName = fileName + "_";
        std::cout << "Input the number of files to be merged: ";
        int fileNum;
        std::cin >> fileNum;
        std::cout << std::endl;
        
        for (int i = 0; i < fileNum; i++) {
          fileData targetFile;
          std::cout << "Input 201, 202, ...[0]Quit): ";
          targetFileName = getExistFileName("copy");
          std::cout << std::endl;

          if (targetFileName == "0") break;

          outputFileName += targetFileName;
          if (i != fileNum - 1) {
            outputFileName += "_";
          }
          targetFile.readFromFile("copy" + targetFileName + ".txt", false);
        
          file = file.mergeWith(targetFile);
          //debug
          // std::cout << "i=" << i << "fileNum = " << file.getSize() << std::endl;
        }
        outputFileName = "output" + outputFileName;
        file.writeToFile(outputFileName);
        std::cout << "Number of records = " << file.getSize() << std::endl;
      }
    } else {
      std::cout << "Command does not exist!" << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}



