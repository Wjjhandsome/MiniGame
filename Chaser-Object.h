#pragma once
#include <random>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
class Ground
{//�ܵ�
public:
	Ground();
	~Ground();
	Ground(int len);
	int GetLength();
	int length = 1000;
};
class Car : public Ground
{//����
public:
	Car();
	~Car();
	Car(int fue, int spea, int loc , int orien , int j);
	int GetFuel() const;
	void SetFuel(int fuel);
	int GetSpead() const;
	void SetSpead(int spea);
	int GetLocation() const;
	void SetLocation(int location);
	bool drive();
	void SetOrientation();
	int Getx();
	int GetOrientation();
	int length = 1000;
	int GetLength();
	int trans;
private:
	int fuel;//ȼ��
	int spead;
	int location;
	int x;//λ��
	int orientation;
};
class GasStation : public Ground
{//����վ
public:
	GasStation();
	~GasStation();
	GasStation(int fue, int loc);
	int GetLocation() const;
	void SetLocation(int location);
	bool CheckFuel() const;
	int GetFuel() const;
	void SetFuel(int location);
	int length = 1000;
private:
	int fuel;
	int location;
};
enum class PhaseLoop
{
	BeforeMainLoop,
	DuringMainLoop,
	AfterMainLoop
};
/// <summary>
/// ���ڿ�����Ϸ���������ȼ��ȱʧ�����ʹ����Լ��ɹ�ͨ��
/// </summary>
enum class Result {
	FuelLack, 
	Fuelerror,
	MissionACComplished
};
/// <summary>
/// ���ڿ�����Ϸ״̬��������ҳ�棬������Ϸ���У�������Ϸ�Ѿ����
/// </summary>
enum class FirstGameState {
	MAIN_MENU = 0,
	Level1_RUNNING = 1,
	Level2_RUNNING = 2,
	Level3_RUNNING = 3,
	Level4_RUNNING = 4,
	Level5_RUNNING = 5,
};

int modify(int a, int b);
bool CheckCarSta(Car car , GasStation sta , int e);
bool CarReplenishFuel(Car &car, GasStation &sta, int a , int e);
std::vector<int> generateRandomArray(int c, int a , bool k);
std::vector<Car>  CarGenerate(int c , int spea , int loc , int orien);
std::vector<GasStation>  StationGenerate(int c, int len ,int sum );
Result playCar(Car car , std::vector<GasStation> sta , std::vector<int> plan , int y);
Result playCar(Car car1, Car car2, std::vector<GasStation> sta, std::vector<int> plan1, std::vector<int> plan2, int y);
//�߼���Ȼ�������⣬����˵0��lenth��������ͬһ��λ��
std::pair<int, int> popMinValue(std::vector<int>& vec);
void Car1_load(PhaseLoop phase, int x, int y);
void Car2_load(PhaseLoop phase, int x, int y);
void Ground_load(PhaseLoop phase , int y);
void station_load(PhaseLoop phase , int y , std::vector<int> loc);
void Query_load(PhaseLoop phase, int x, int y);
void Star_load(PhaseLoop phase, int x, int y);
void Door_load(PhaseLoop phase , int x, int y);
bool game(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font);
bool level1(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state);
bool level2(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state);
bool level3(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state);
bool level4(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state);
bool level5(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state);
void InfoMenu(std::vector<std::string> info , ALLEGRO_FONT* font);
bool GameState(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font , Result &res , FirstGameState &state);
void Congratulation_load(PhaseLoop phase, int x, int y);
//����һ����Ϣ��ʾ
bool compareByValue(const GasStation a, const GasStation b);
