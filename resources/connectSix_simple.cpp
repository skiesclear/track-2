
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>



#define GRIDSIZE 15
#define judge_black 0
#define judge_white 1
#define grid_blank 0
#define grid_black 1
#define grid_white -1

using namespace std;

int currBotColor; // ������ִ����ɫ��1Ϊ�ڣ�-1Ϊ�ף�����״̬��ͬ��
int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; // ��x��y����¼����״̬
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };

// �ж��Ƿ���������
inline bool inMap(int x, int y)
{
	if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
		return false;
	return true;
}


// �����괦���ӣ�����Ƿ�Ϸ���ģ������
bool ProcStep(int x0, int y0, int x1, int y1, int grid_color, bool check_only)
{
	if (x1 == -1 || y1 == -1) {
		if (!inMap(x0, y0) || gridInfo[x0][y0] != grid_blank)
			return false;
		if (!check_only) {
			gridInfo[x0][y0] = grid_color;
		}
		return true;
	}
	else {
		if ((!inMap(x0, y0)) || (!inMap(x1, y1)))
			return false;
		if (gridInfo[x0][y0] != grid_blank || gridInfo[x1][y1] != grid_blank)
			return false;
		if (!check_only) {
			gridInfo[x0][y0] = grid_color;
			gridInfo[x1][y1] = grid_color;
		}
		return true;
	}
}

int main()
{
	int x0, y0, x1, y1;

	// �����Լ��յ���������Լ���������������ָ�����״̬
	int turnID;
	cin >> turnID;
	currBotColor = grid_white; // �ȼ����Լ��ǰ׷�
	for (int i = 0; i < turnID; i++)
	{
		// ������Щ��������𽥻ָ�״̬����ǰ�غ�
		cin >> x0 >> y0 >> x1 >> y1;
		if (x0 == -1)
			currBotColor = grid_black; // ��һ�غ��յ�������-1, -1��˵�����Ǻڷ�
		if (x0 >= 0)
			ProcStep(x0, y0, x1, y1, -currBotColor, false); // ģ��Է�����
		if (i < turnID - 1) {
			cin >> x0 >> y0 >> x1 >> y1;
			if (x0 >= 0)
				ProcStep(x0, y0, x1, y1, currBotColor, false); // ģ�⼺������
		}
	}



	/************************************************************************************/
	/***�����������Ĵ��룬���߽�������������ӵ�λ�ã�����startX��startY��resultX��resultY��*****/
	//�����Ϊ������Ե�ʾ�����룬��Ч�ʵͣ���ɾ��
	int startX, startY, resultX, resultY;
	int beginPos[GRIDSIZE*GRIDSIZE][2], possiblePos[GRIDSIZE*GRIDSIZE][2];
	bool selfFirstBlack = (turnID == 1 && currBotColor == grid_black);//�����Ǻڷ�����

	int posCount = 0, choice0, choice1;
	for (int i = 0; i < GRIDSIZE; ++i) {
		for (int j = 0; j < GRIDSIZE; ++j) {
			if (gridInfo[i][j] == grid_blank) {
				beginPos[posCount][0] = i;
				beginPos[posCount][1] = j;
				possiblePos[posCount][0] = i;
				possiblePos[posCount++][1] = j;
			}
		}
	}
	// ��������
	if (posCount > 0){
		srand(time(0));
		choice0 = rand() % posCount;
		startX = beginPos[choice0][0];
		startY = beginPos[choice0][1];
		choice1 = rand() % posCount;
		if (selfFirstBlack) {   //�ڷ�����ֻ��һ��
			resultX = -1;
			resultY = -1;
		}
		else {
			while (choice0 == choice1) {
				choice1 = rand() % posCount;
			}
			resultX = possiblePos[choice1][0];
			resultY = possiblePos[choice1][1];
		}
	}
	else {
		startX = -1;
		startY = -1;
		resultX = -1;
		resultY = -1;
	}
	/****���Ϸ������Ĵ��룬���߽�������������ӵ�λ�ã�����startX��startY��resultX��resultY��****/
	/************************************************************************************/

	// ���߽�������ƽ̨������߽��

	cout << startX << ' ' << startY << ' ' << resultX<< ' '<< resultY<< endl;
	return 0;
}