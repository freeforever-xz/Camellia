#include"FileName1.cpp";
//随机生成一个数字   
struct Player 
{
	string name;
	int occurs;
};
// 排序规则：按猜中次数升序（次数越少，排名越靠前）
bool comparePlayer(const Player& p1, const Player& p2) 
{
	return p1.occurs < p2.occurs;
}
// 从文件读取排行榜数据
vector<Player> readRanking() 
{
	vector<Player> players;
	ifstream inFile("ranking.txt");
	if (inFile.is_open()) {
		Player p;
		while (inFile >> p.name >> p.occurs) {
			players.push_back(p);
		}
		inFile.close();
	}
	return players;
}
// 向文件写入排行榜数据
void writeRanking(const vector<Player>& players)
{
	ofstream outFile("ranking.txt");
	if (outFile.is_open()) {
		for (const auto& p : players) {
			outFile << p.name << " " << p.occurs << endl;
		}
		outFile.close();
	}
}
// 显示排行榜
void showRanking() {
	vector<Player> players = readRanking();
	sort(players.begin(), players.end(), comparePlayer);
	cout << "\n===== 猜数字游戏排行榜 =====" << endl;
	if (players.empty()) {
		cout << "暂无排行榜记录~" << endl;
	}
	else {
		for (size_t i = 0; i < players.size(); ++i) {
			cout << i + 1 << ". " << players[i].name << " - " << players[i].occurs << "次猜中" << endl;
		}
	}
}

int main()
{
	string Playername;
	cout<<"=============欢迎来到猜数字游戏============" << endl;
	cout << "请输入你的呢称" << endl;
	cin >> Playername;
    //随机生成1-100的数字
	srand((unsigned int)time(NULL));//设置随机数种子
	int num = rand() % 100 + 1;//生成1-100的数字
	int guess = 0;
	cout << "请输入1-100的数字" << endl;
	int occur = 0;//记录猜测次数occur

	//玩家猜测数字
	do
	{
		occur++;
		cin >> guess;
		if (guess < 1 || guess>100)
		{
			cout << "请认真审题！" << endl;
		}
		else if (guess > num)
		{
			cout << "oh no！猜大啦！再试一次吧！" << endl;
			cout << "这是第" << occur << "次猜测" << endl;
		}
		else if (guess < num)
		{
			cout << "oh no！猜小啦！再试一次吧！" << endl;
			cout << "这是第" << occur << "次猜测" << endl;
		}
		else
		{
			cout << "恭喜你在第" << occur << "次猜对啦！" << endl; 
			cout << "答案就是" << num << endl;
			cout << "===========游戏结束==========" << endl;
			//读取现有排行榜数据
			vector<Player>players = readRanking();
			//添加当前玩家数据
			players.push_back({ Playername,occur });
			//排序后写入文件
			sort(players.begin(), players.end(), comparePlayer);
			writeRanking(players);
			//显示排行榜
			showRanking();
			break;
		}
	} while (1);
	char playagain;
		cout << "是否再来一局？(y/n)" << endl;
		cin >> playagain;
		if (playagain == 'y' || playagain == 'Y')
		{
			main();//递归调用main函数实现重新开始游戏
		}
		else
		{
			cout << "感谢你的参与，期待下次再见！" << endl;
		}
	return 0;
}







