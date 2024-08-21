#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

#define N 5
#define INF 10e7
#define min(a,b) ((a>b)?b:a)

static const int M = 1 << (N - 1);
//�洢����֮��ľ���
int g[N][N] = { {0,3,INF,8,9},
               {3,0,3,10,5},
               {INF,3,0,4,3},
               {8,10,4,0,20},
               {9,5,3,20,0} };
//���涥��i��״̬s���ص���ʼ�����С����
int dp[N][M];
//����·��
vector<int> path;

//���ĺ����������̬�滮dp����
void TSP() {
    //��ʼ��dp[i][0]
    for (int i = 0; i < N; i++) {
        dp[i][0] = g[i][0];
    }
    //���dp[i][j],�ȸ������ڸ�����
    for (int j = 1; j < M; j++) {
        for (int i = 0; i < N; i++) {
            dp[i][j] = INF;
            //�������j(��״̬j)�а������i,�򲻷��������˳���
            //��ʾ����߹��ļ����а���i�����
            if (((j >> (i - 1)) & 1) == 1) {//ʣ����а�����������ֱ��������������
                continue;
            }
            //�����ʾ�߹��Ľڵ㵱�в�����i
            //Ȼ���ж�״̬j���а�����·���ĳ��� Ҳ���Ƕ�������Ϊһ
            for (int k = 1; k < N; k++) {
                //�жϵ� k �������Ƿ��߹� ����ǵ�kλ��0���ʾû���߹�����
                if (((j >> (k - 1)) & 1) == 0) {
                    continue;
                }
                // ʣ����а�����������
                //����ö���м�ڵ�k��������С����
                if (dp[i][j] > g[i][k] + dp[k][j ^ (1 << (k - 1))]) {
                    dp[i][j] = g[i][k] + dp[k][j ^ (1 << (k - 1))];
                }
            }
        }
    }

}
//�жϽ���Ƿ��Է���,������0�Ž��
bool isVisited(bool visited[]) {
    for (int i = 1; i < N; i++) {
        if (visited[i] == false) {
            return false;
        }
    }
    return true;
}
//��ȡ����·����������path��,���ݶ�̬�滮��ʽ�����ҳ����·�����
void getPath() {
    //��Ƿ�������
    bool visited[N] = { false };
    //ǰ���ڵ��� S=M-1��ʾ������λȫһ �ڼ�λ�Ķ�����λΪһ��ʾ������л�û�߹�
    int pioneer = 0, min = INF, S = M - 1, temp;
    //��������ż�������
    path.push_back(0);

    while (!isVisited(visited)) {
        for (int i = 1; i < N; i++) {
            //S�ж�����λλ0��ʾ��ǰ�����Լ��߹�
            if (visited[i] == false && (S & (1 << (i - 1))) != 0) {
                if (min > g[pioneer][i] + dp[i][(S ^ (1 << (i - 1)))]) {
                    min = g[pioneer][i] + dp[i][(S ^ (1 << (i - 1)))];
                    temp = i;
                }
            }
        }
        pioneer = temp;
      //  ���μ�¼��С·��
        path.push_back(pioneer);
        visited[pioneer] = true;
        S = S ^ (1 << (pioneer - 1));
        min = INF;
    }
}
//���·��
void printPath() {
    cout << "��С·��Ϊ��";
    vector<int>::iterator  it = path.begin();
    for (it; it != path.end(); it++) {
        cout << *it << "--->";
    }
    //������������
    cout << 0;
}

int main()
{
    TSP();
    cout << "��СֵΪ��" << dp[0][M - 1] << endl;
    getPath();
    printPath();
    return 0;
}