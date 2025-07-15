#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>

// 檢查檔案是否存在
bool fileExist(std::string fileName) {
  std::ifstream file(fileName);
  return file.is_open();
}

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

// 輸入0 return false 直到拿到正確輸出 return true
bool getFileName(std::string& fileName) {
  while (1) {
    std::cout << "Input a file number [0: quit]: ";
    std::cin >> fileName;
    

    if (fileName == "0") {
      std::cout << std::endl;
      return false;
    }
    

    if (!fileExist("input" + fileName + ".txt")) {
      std::cout << std::endl << "### input" + fileName + ".txt does not exist! ###" << std::endl << std::endl;
      continue; 
    } else break;
  }
  return true;
}

int getThreshold(int maxHP) {
  std::string threshold;
  int value;

  std::cout << "Threshold (a positive integer): ";
  std::cin >> threshold;

  while (1) {
    try {
      value = std::stoi(threshold);
      
      if (value > maxHP) {
        std::cout << std::endl << "### It is NOT in [1," << maxHP << "]. ###" << std::endl;
      } else if (value < 1) {
        std::cout << "### It is NOT a positive integer. ###" << std::endl;
      } else break;
    } catch (std::invalid_argument) {
      std::cout << "### It is NOT a positive integer. ###" << std::endl;
    }
    std::cout << "Try again: ";
    std::cin >> threshold;
  }
  return value;
}



class Pokemon {
 private:
  int id;
  std::string name;
  std::string type1;
  std::string type2;
  int total;
  int HP;
  int attack;
  int defense;
  int spAtk;
  int spDef;
  int speed;
  int generation;
  bool legendary;
 public:
  Pokemon() {}
  Pokemon(int id, std::string& name, std::string& type1, std::string& type2,
          int total, int HP, int attack, int defense, int spAtk, int spDef, int speed,
          int generation, bool legendary)
        : id(id), name(name), type1(type1), type2(type2), total(total), HP(HP),
          attack(attack), defense(defense), spAtk(spAtk), spDef(spDef), speed(speed),
          generation(generation), legendary(legendary) {}
  int getId() { return id; }

  std::string getName() { return name; }

  std::string getType1() { return type1; }

  std::string getType2() { return type2; }

  int getTotal() { return total; }

  int getHP() { return HP; }

  int getAttack() { return attack; }

  int getDefense() { return defense; }

  int getSpAtk() { return spAtk; }

  int getSpDef() { return spDef; }

  int getSpeed() { return speed; }

  int getGeneration() { return generation; }

  std::string getLegendary() { 
    std::string str;
    if (legendary) {
      str = "TRUE";
    } else {
      str = "FALSE";
    }
    return str; 
  }

  void printPokemon() {
    std::cout << id << '\t' << name << '\t' << type1 << '\t' << type2 
              << '\t' << HP << '\t' << attack << '\t' << defense << std::endl;
  }
};

class Pokemons { 
 private:
  
  std::vector<Pokemon> pokemons;
 
 public:

  std::vector<Pokemon>& getPokemons() {
    return pokemons;
  }
  
  void addPokemon(Pokemon& pokemon) {
    pokemons.push_back(pokemon);
  }
  // ture 有內容 false 為空
  bool readFormFile(std::string fileName) {
    std::ifstream file(fileName);
    std::string line;
    if (!getline(file, line)) {
      return false;
    }

    std::string name, type1, type2;
    int id, total, HP, attack, defense, spAtk, spDef, speed, generation;
    bool legendary;

    while (getline(file, line)) {
      std::istringstream iss(line);
      std::string data;
      int dataCount = 0;
      while (getline(iss, data, '\t')) {
        
        switch (dataCount) {
          case 0: id = stoi(data); break;
          case 1: name = data; break;
          case 2: type1 = data; break;
          case 3: type2 = data; break;
          case 4: total = stoi(data); break;
          case 5: HP = stoi(data); break;
          case 6: attack = stoi(data); break;
          case 7: defense = stoi(data); break;
          case 8: spAtk = stoi(data); break;
          case 9: spDef = stoi(data); break;
          case 10: speed = stoi(data); break;
          case 11: generation = stoi(data); break;
          case 12: legendary = (data == "TRUE"); break;
          default: break;
        }       
        dataCount++;
      }
      Pokemon pokemon(id, name, type1, type2, total, HP, attack, defense, spAtk, spDef, speed, generation, legendary);
      pokemons.push_back(pokemon);
    }

    file.close();
    return true;
  }
  void printPokemons() {
        std::cout << '\t' << "#" << '\t' << std::setw(24) << std::left << "Name" << '\t' << std::setw(10) << "Type 1" 
                  << '\t' << "HP" << '\t' << "Attack" << '\t' << "Defense" << std::endl;
    int count = 1;
      for (Pokemon pokemon: pokemons) {
        std::cout << "[" << std::setw(3) << std::right << count << "]" << '\t' << pokemon.getId() << '\t' << std::setw(24) << std::left << pokemon.getName() << '\t' << std::setw(10) << pokemon.getType1() 
                  << '\t' << std::setw(6) << pokemon.getHP() << '\t' << pokemon.getAttack() << '\t' << pokemon.getDefense() << std::endl;
        count++;
      }
  }

  int getPokemonNum() {
    return pokemons.size();
  }

  Pokemon& getPokemonAt(int n) {
    if (n < 0 || n >= pokemons.size()) {
      throw std::out_of_range("Index out of range.");
    } else {
      return pokemons.at(n);
    }
  }
};


class BST {
 private:
  struct Node {
    Pokemons pokemons;
    Node* left;
    Node* right;

    Node(Pokemon& pokemon) : left(nullptr), right(nullptr) {
      pokemons.addPokemon(pokemon);
    }

    Pokemons getPokemons() {
      return pokemons;
    }
  };

  Node* root;

 public:
  BST() : root(nullptr) {}

  ~BST() {
    deleteTree(root);
  }

  bool treeEmpty() {
    if (root == nullptr) return true;
    else return false;
  }



  void rebuildTree(Pokemons& pokemons) {
    // 先清空樹
    deleteTree(root);
    // root = nullptr;
    // 建樹
    insert(pokemons);
  }

  void deleteTree() {
    deleteTree(root);
  }

  void deleteTree(Node*& node) {
    if (node == nullptr) return;
    deleteTree(node->left);  
    deleteTree(node->right);
    delete node;    
    node = nullptr;        
  }

  Node* getRoot() {return root;}
  
  // 找最大血量
  int getMaxHP() {
    if (root == nullptr) return 0;
    Node* node = root;
    int maxHp;
    while (node != nullptr) {
      if (node->right == nullptr) {
        maxHp = node->pokemons.getPokemonAt(0).getHP();
        break;
      } else node = node->right;
    }
    return maxHp;
  }

  void insert(Pokemon& pokemon) {
    if (root == nullptr) {
      root = new Node(pokemon);
      return;
    }

    Node* curNode = root;

    while (curNode != nullptr) {
      if (pokemon.getHP() == curNode->pokemons.getPokemonAt(0).getHP()) {
        curNode->pokemons.addPokemon(pokemon);
        return;
      } else if (pokemon.getHP() > curNode->pokemons.getPokemonAt(0).getHP()) {
        if (curNode->right == nullptr) {
          curNode->right = new Node(pokemon);
          return;
        } else {
          curNode = curNode->right;
        }
      } else if (pokemon.getHP() < curNode->pokemons.getPokemonAt(0).getHP()) {
        if (curNode->left == nullptr) {
          curNode->left = new Node(pokemon);
          return;
        } else {
          curNode = curNode->left;
        }
      }
    }
  }

  void insert(Pokemons& pokemons) {
    for (int i = 0; i < pokemons.getPokemonNum(); i++) {
      insert(pokemons.getPokemonAt(i));
    }
  }
  // debug
  void inorderTraversal() {
    std::cout << '\t' << "#" << '\t' << "Name" << '\t' << "Type 1" << '\t' << "HP" << '\t' << "Attack" << '\t' << "Defense" << std::endl;
    int count = 1;
    inorderRecursive(root, count);
  }
  // debug
  void inorderRecursive(Node* node, int& count) {
    if (node != nullptr) {
      inorderRecursive(node->left, count);
      Pokemons nodePokemons = node->pokemons;
      for (int i = 0; i < nodePokemons.getPokemonNum(); i++) {
        Pokemon pokemon = nodePokemons.getPokemonAt(i);
        std::cout << "[  " << count << "]" << '\t' << pokemon.getId() << '\t' << pokemon.getName() << '\t' << pokemon.getType1() 
                  << '\t' << pokemon.getHP()<< '\t' << pokemon.getAttack()<< '\t' << pokemon.getDefense() << std::endl;
        count++;
      }
      inorderRecursive(node->right, count);
    }
  }

  int getHeight() {
    return getHeightRecursive(root);
  }

  int getHeightRecursive(Node* node) {
    if (node == nullptr) {
      return 0;
    }

    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);

    return 1 + std::max(leftHeight, rightHeight);
  }

  // ---------
  int searchWithLimitIncrease(int n) {
    int visitedNodes = 0;
    int totalNum = 1;          
    std::cout << '\t' << "#" << '\t' << std::setw(24) << std::left << "Name" << '\t' << std::setw(10) << "Type 1" << '\t' << "Total"
              << '\t' << "HP" << '\t' << "Attack" << '\t' << "Defense" << std::endl;
    searchListIncrease(root, n, visitedNodes, totalNum);
    return visitedNodes;
  }

  // list hp increase
  void searchListIncrease(Node* node, int n, int& visitedNodes, int& totalNum) {
    if (node == nullptr) return;

    if (node->pokemons.getPokemonAt(0).getHP() > n) {
      visitedNodes++;
      searchListIncrease(node->left, n, visitedNodes, totalNum);
      for (int i = 0; i < node->pokemons.getPokemonNum(); i++) {
        Pokemon pokemon = node->pokemons.getPokemonAt(i);
        std::cout << "[" << std::setw(3) << std::right << totalNum << "]" << '\t' << pokemon.getId() << '\t' << std::setw(24) << std::left << pokemon.getName() << '\t' << std::setw(10) << pokemon.getType1() 
                  << '\t' << std::setw(6) << pokemon.getTotal() << '\t' << pokemon.getHP() << '\t' << pokemon.getAttack() << '\t' << pokemon.getDefense() << std::endl;;
        totalNum++;
      }
      searchListIncrease(node->right, n, visitedNodes, totalNum);
    } else if (node->pokemons.getPokemonAt(0).getHP() == n) {
      visitedNodes++;
      
      for (int i = 0; i < node->pokemons.getPokemonNum(); i++) {
        Pokemon pokemon = node->pokemons.getPokemonAt(i);
        std::cout << "[" << std::setw(3) << std::right << totalNum << "]" << '\t' << pokemon.getId() << '\t' << std::setw(24) << std::left << pokemon.getName() << '\t' << std::setw(10) << pokemon.getType1() 
                  << '\t' << std::setw(6) << pokemon.getTotal() << '\t' << pokemon.getHP() << '\t' << pokemon.getAttack() << '\t' << pokemon.getDefense() << std::endl;;
        totalNum++;
      }
      searchListIncrease(node->right, n, visitedNodes, totalNum);
    } else if (node->pokemons.getPokemonAt(0).getHP() < n) {
      visitedNodes++;
      searchListIncrease(node->right, n, visitedNodes, totalNum);
    }
  }
  // ---------


  int searchWithLimitDecrease(int n) {
    int visitedNodes = 0;
    int totalNum = 1;          
    std::cout << '\t' << "#" << '\t' << std::setw(24) << std::left << "Name" << '\t' << std::setw(10) << "Type 1" << '\t' << "Total"
              << '\t' << "HP" << '\t' << "Attack" << '\t' << "Defense" << std::endl;
    searchListDecrease(root, n, visitedNodes, totalNum);
    return visitedNodes;
  }
  // list hp increase
  void searchListDecrease(Node* node, int n, int& visitedNodes, int& totalNum) {
    if (node == nullptr) return;

    if (node->pokemons.getPokemonAt(0).getHP() > n) {
      visitedNodes++;
      searchListDecrease(node->right, n, visitedNodes, totalNum);
      for (int i = 0; i < node->pokemons.getPokemonNum(); i++) {
        Pokemon pokemon = node->pokemons.getPokemonAt(i);
        std::cout << "[" << std::setw(3) << std::right << totalNum << "]" << '\t' << pokemon.getId() << '\t' << std::setw(24) << std::left << pokemon.getName() << '\t' << std::setw(10) << pokemon.getType1() 
                  << '\t' << std::setw(6) << pokemon.getTotal() << '\t' << pokemon.getHP() << '\t' << pokemon.getAttack() << '\t' << pokemon.getDefense() << std::endl;;
        totalNum++;
      }
      searchListDecrease(node->left, n, visitedNodes, totalNum);
    } else if (node->pokemons.getPokemonAt(0).getHP() == n) {
      visitedNodes++;
      searchListDecrease(node->right, n, visitedNodes, totalNum);
      for (int i = 0; i < node->pokemons.getPokemonNum(); i++) {
        Pokemon pokemon = node->pokemons.getPokemonAt(i);
        std::cout << "[" << std::setw(3) << std::right << totalNum << "]" << '\t' << pokemon.getId() << '\t' << std::setw(24) << std::left << pokemon.getName() << '\t' << std::setw(10) << pokemon.getType1() 
                  << '\t' << std::setw(6) << pokemon.getTotal() << '\t' << pokemon.getHP() << '\t' << pokemon.getAttack() << '\t' << pokemon.getDefense() << std::endl;;
        totalNum++;
      }
    } else if (node->pokemons.getPokemonAt(0).getHP() < n) {
      visitedNodes++;
      searchListDecrease(node->right, n, visitedNodes, totalNum);
    }
  }



  // void deleteMaxHP() {

  //   bool treeEmpty = false;
  //   Node* node = root;
  //   Node* preNode = nullptr;

  //   while (node->right != nullptr) {
  //       preNode = node;
  //       node = node->right;
  //   }

  //   Pokemon printPokemon;

  //   if (node->pokemons.getPokemonNum() == 1) {
  //     printPokemon = node->pokemons.getPokemonAt(0);
  //     if (preNode == nullptr) {
  //       if (node->left == nullptr) {
  //         root = nullptr;
  //         treeEmpty = true;
  //       } else {
  //         root = node->left;
  //       }
        
  //     } else if (node->left == nullptr) { 
  //         preNode->right = nullptr; 
  //     } else {
  //         preNode->right = node->left; 
  //     }

  //     delete node; 

  //   } else {
  //     printPokemon = node->pokemons.getPokemonAt(0);
  //     node->pokemons.getPokemons().erase(node->pokemons.getPokemons().begin());
  //   }
 

  //   std::cout << "#" << '\t' << "Name" << '\t' << "Type 1" << '\t' << "Type 2"<< '\t' << "Total"
  //             << '\t' << "HP" << '\t' << "Attack" << '\t' << "Defense" << '\t' << "Sp. Atk" << '\t' << "Sp. Def" << '\t' << "Speed" 
  //             << '\t' << "Generation" << '\t' << "Legendary"<< std::endl; 

  //   Pokemon pok = printPokemon;
  //       std::cout << pok.getId() << '\t' << pok.getName() << '\t' << pok.getType1() << '\t' << pok.getType2()
  //                 << '\t' << pok.getTotal() << '\t' << pok.getHP() << '\t' << pok.getAttack() << '\t' << pok.getDefense() 
  //                 << '\t' << pok.getSpAtk()  << '\t' << pok.getSpDef() << '\t' << pok.getSpeed() << '\t' << pok.getGeneration() << '\t' << pok.getLegendary() << std::endl;

  // }
  // gpt version
  void deleteMaxHP() {
    if (root == nullptr) {
        std::cout << "Tree is already empty!" << std::endl;
        return;
    }

    Node* node = root;
    Node* parent = nullptr;

    // 找到最右側的節點（最大 HP 節點）
    while (node->right != nullptr) {
        parent = node;
        node = node->right;
    }

    Pokemon printPokemon = node->pokemons.getPokemonAt(0);

    if (node->pokemons.getPokemonNum() > 1) {
        // 如果節點有多個 Pokemon，僅刪除其中一個
        node->pokemons.getPokemons().erase(node->pokemons.getPokemons().begin());
    } else {
        // 如果節點只有一個 Pokemon，需要刪除整個節點
        if (parent == nullptr) {
            // 如果節點是根節點
            root = node->left; // 左子樹取代根節點
        } else if (parent->right == node) {
            parent->right = node->left; // 將父節點的右子節點設為當前節點的左子節點
        }

        delete node;
    }

    // 印出被刪除的 Pokemon
    std::cout << "#" << '\t' << "Name" << '\t' << "Type 1" << '\t' << "HP" << '\t' << "Attack" << '\t' << "Defense" << std::endl;
    std::cout << printPokemon.getId() << '\t' << printPokemon.getName() << '\t' << printPokemon.getType1()
              << '\t' << printPokemon.getHP() << '\t' << printPokemon.getAttack() << '\t' << printPokemon.getDefense() << std::endl;
  }

};


int main() {

  bool treeEmpty = true;
  BST bst;

  while (1) {
    std::string command, fileName;
  
    std::cout << "*** Binary Search Tree on Pokemon ***" << std::endl;
    std::cout << "* 0. QUIT                           *" << std::endl;
    std::cout << "* 1. Read one file to build BST     *" << std::endl;
    std::cout << "* 2. Threshold search on one column *" << std::endl;
    std::cout << "* 3. Delete the max on one column   *" << std::endl;
    std::cout << "*************************************" << std::endl;

    std::cout << "Input a choice(0, 1, 2, 3): ";
    std::cin >> command;
    // 不是任務二就要換行
    if (command != "2" && command != "3") std::cout << std::endl;
    
    if (command == "0") break;
    else if (command == "1" || command == "2" || command == "3") {
      if (command == "1") {

        Pokemons pokemons;
        // 如果return false 表示輸入0 退出
        if (getFileName(fileName)) {
          treeEmpty = false;

          if (!pokemons.readFormFile("input" + fileName + ".txt")) {
            std::cout << "### Get nothing from the file input" + fileName + ".txt ! ###" << std::endl << std::endl;
            continue;
          }

          // pokemons.printPokemons();
          bst.rebuildTree(pokemons);
          std::cout << "HP tree height = " << bst.getHeight() << std::endl << std::endl;

        } else {
          treeEmpty = true;
          bst.deleteTree();
        }      
      } else if (command == "2") {

        if (treeEmpty) {
          std::cout << std::endl << "----- Execute Mission 1 first! -----" << std::endl << std::endl;
          continue;
        }
        
        int threshold = getThreshold(bst.getMaxHP());
        int visitedNodes = bst.searchWithLimitDecrease(threshold);
        std::cout << "Number of visited nodes = " << visitedNodes << std::endl << std::endl;

        // visitedNodes = bst.searchWithLimitIncrease(threshold);
        // std::cout << "Number of visited nodes = " << visitedNodes << std::endl << std::endl;

      } else if (command == "3") {
        
        if (treeEmpty) {
          std::cout << std::endl << "----- Execute Mission 1 first! -----" << std::endl << std::endl;
          continue;
        }


        bst.deleteMaxHP();
        if (bst.treeEmpty()) {
          treeEmpty = true;
        }

        std::cout << "HP tree height = " << bst.getHeight() << std::endl << std::endl;
      }

    } else {
      std::cout << "Command does not exist!" << std::endl << std::endl;
    } 
  }
}

