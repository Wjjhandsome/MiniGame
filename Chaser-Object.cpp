#include "Chaser-Object.h"
#include <random>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>
#include <iostream>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Draw.h"
Car::Car()
{
	fuel = 0;
	spead = 0;
	location = 0;
}
/// <summary>
/// �����ӻ��߼�ȼ��
/// </summary>
/// <param name="fue"></param>
void Car::SetFuel(int fue)
{
	fuel += fue;
}
/// <summary>
/// ��ȡ������ǰȼ�ϲ�����
/// </summary>
/// <returns></returns>
int Car::GetFuel() const 
{
	return fuel;
}
/// <summary>
/// ��ȡ�����ٶȲ�����
/// </summary>
/// <returns>int</returns>
int Car::GetSpead() const 
{ 
	return spead;
}
/// <summary>
/// ���ó����ٶ�
/// </summary>
/// <param name="spea"></param>
void Car::SetSpead(int spea) 
{
	spead += spea;
}
/// <summary>
/// ��ʼ��������ȼ�ϡ��ٶȡ�λ�á��������г̡�
/// </summary>
/// <param name="fue"></param>
/// <param name="spea"></param>
/// <param name="loc"></param>
/// <param name="orien"></param>
/// <param name="j"></param>
Car::Car(int fue, int spea, int loc , int orien , int j) : 
	fuel(fue) , spead(spea) , location(loc) , orientation(orien) , x(j) , trans(0)
{
}
Car::~Car()
{
}
/// <summary>
/// �ƶ�����
/// </summary>
/// <param name="loc"></param>
void Car::SetLocation(int loc)
{
	location += loc;
}
/// <summary>
/// ��ȡ������ǰλ��
/// </summary>
/// <returns></returns>
int Car::GetLocation() const
{
	return location;
}
/// <summary>
/// ��ʻ�������Զ��Ի����ܵ�ȡģ������false˵��û��ȼ��֧�ּ������ˡ�
/// </summary>
bool Car::drive() 
{
	if (location <= 0 && orientation == -1)
	{
		location = length + location;
		return 1;
	}
	else if (location >= length && orientation == 1)
	{
		location = location - length;
		return 1;
	}
	if (fuel >= spead)
	{
		location += spead * orientation;
		fuel -= spead;
		x += spead;
		return 1;
	}
	else if (fuel == spead)
	{
		location += (spead-1) * orientation;
		fuel -= (spead-1);
		x += (spead-1);
	}
	else
	{
		return false;
	}
}
/// <summary>
/// ��ת���ķ���
/// </summary>
void Car::SetOrientation() 
{
	switch (orientation)
	{
	case 1:
		orientation = -1;
		break;
	case -1:
		orientation = 1;
		break;
	}	
}
int Car::Getx() 
{
	return x;
}
int Car::GetOrientation() 
{
	return orientation;
}
int Car::GetLength() 
{
	return length;
}
GasStation::GasStation()
{
	fuel = 0;
	location = 0;
}
GasStation::GasStation(int fue , int loc)
{
	fuel = fue;
	location = loc;
}
GasStation::~GasStation()
{
}
/// <summary>
/// ������վ��ȼ��
/// </summary>
/// <param name="fue"></param>
void GasStation::SetFuel(int fue)
{
	fuel += fue;
}
/// <summary>
/// ��ȡ����վ��ǰȼ�ϲ�����
/// </summary>
/// <returns></returns>
int GasStation::GetFuel() const
{
	return fuel;
}

/// <summary>
/// ���ü���վλ��
/// </summary>
/// <param name="loc"></param>
void GasStation::SetLocation(int loc)
{
	location += loc;
}
/// <summary>
/// ��ȡ����վ��ǰλ��
/// </summary>
/// <returns></returns>
int GasStation::GetLocation() const
{
	return location;
}
/// <summary>
/// ���ؼ���վ�����Ƿ�Ϻ���׼
/// </summary>
/// <returns></returns>
bool GasStation::CheckFuel() const 
{
	if (fuel >= 0);
	{
		return true;
	}
	return false;
}

Ground::Ground()
{
	length = 0.0;
}
Ground::Ground(int len)
{
	length = len;
}
Ground::~Ground()
{
}
/// <summary>
/// ��ȡ�ܵ�����.
/// </summary>
/// <returns></returns>
int Ground::GetLength()
{
	return length;
}
int modify(int a, int b)
{
	int result = a % b;
	// ��� result �Ǹ���������� b �ľ���ֵ
	if (result < 0) {
		result += std::abs(b);
	}
	return result;
}
/// <summary>
/// ��鳵�����վ����Χ���Ƿ���ͬһ�ص�
/// </summary>
/// <param name="car"></param>
/// <param name="sta"></param>
/// <param name="e"></param>
/// <returns></returns>
bool CheckCarSta(Car car , GasStation sta , int e)
{
	if (fabs(car.GetLocation() - sta.GetLocation()) <= e) 
	{
		return true;
	}
	return false;
}
/// <summary>
/// �������ɳ�������cΪ������speaΪ�ٶȣ�locΪ��ʼλ��
/// </summary>
/// <param name="c"></param>
/// <param name="spea"></param>
/// <param name="loc"></param>
std::vector<Car> CarGenerate(int c, int spea, int loc , int orien)
{
	std::vector<Car> objects;
	for (int i = 0; i < c; ++i) {
		objects.emplace_back(0 , spea , loc , orien , 0); // ʹ�� emplace_back ֱ�ӹ������
	}
	return objects;
}
/// <summary>
/// lenΪ�ܳ��ȣ�cΪ����վ������sumΪ�����ܺͣ�nΪ������Ҫ��������С����
/// </summary>
/// <param name="c"></param>
/// <param name="len"></param>
/// <param name="sum"></param>
/// <param name="n"></param>
/// <returns>vector</returns>
std::vector<GasStation> StationGenerate(int c, int len, int sum )
{
	std::vector<int> fuearray(c) , locarray; 
	fuearray = generateRandomArray(c, sum , true);
	locarray = generateRandomArray(c, len , false);
	std::vector<GasStation> stavec;
	for (int i = 0; i < c; i++)
	{
		stavec.emplace_back(fuearray[i], locarray[i]);
	}
	std::sort(stavec.begin(), stavec.end(), compareByValue);
	return stavec;
}
bool compareByValue(const GasStation a, const GasStation b) {
	return a.GetLocation() < b.GetLocation();
}
/// <summary>
/// ʵ�������ڼ���վ���ͣ��Ƿ�Ӧ����������������¼�����վ����������ĳһʱ��loc�������ˣ��ͼ���
/// </summary>
/// <param name="car"></param>
/// <param name="sta"></param>
/// <param name="a"></param>
/// <param name="e"></param>
bool CarReplenishFuel(Car& car, GasStation& sta, int a , int e)
{
	if (CheckCarSta(car , sta , 4*e))
	{
		if (sta.GetFuel() < a)
		{
			return false;
		}
		car.SetFuel(a);
		sta.SetFuel(-a);
		return true;
	}
	return true;
}

/// <summary>
/// �ú����������ɴ�СΪc�ı���nλС�����飬���Ϊa��kֵ��ʾ�Ƿ���Ҫ�ܺ�Ϊa
/// </summary>
/// <param name="c"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="k"></param>
/// <returns></returns>
std::vector<int> generateRandomArray(int c , int a , bool k) {
	std::vector<int> array(c);
	// ��ʼ�������������
	//Ҫȡ��[a, b) �����������ʹ��(rand() % (b - a)) + a;
	//Ҫȡ��[a, b] �����������ʹ��(rand() % (b - a + 1)) + a;
	//Ҫȡ��(a, b] �����������ʹ��(rand() % (b - a)) + a + 1;
	std::srand(static_cast<unsigned int>(std::time(0)));
	// �������������
	for (int i = 0; i < c; ++i) {
		int value = static_cast<int>((std::rand() % (a+1)))  ;
		array[i] = value;
	}
	// ���㵱ǰ����Ԫ�ص��ܺ�
	if (k)
	{
		int currentSum = std::accumulate(array.begin(), array.end(), 0);
		// �����������
		double scale = static_cast<double>(a) / currentSum;
		// ��������Ԫ����ʹ���ܺ�Ϊ a
		for (int& num : array) {
			num = static_cast<int>(num * scale);
		}
		int adjusted_sum = std::accumulate(array.begin(), array.end(), 0);
		int difference = a - adjusted_sum;
		array.back() += difference;
	}
	return array;
}

Result playCar(Car car1, Car car2, std::vector<GasStation> sta, std::vector<int> plan1, std::vector<int> plan2, int y)
{
	//�������ó��ӵ���ÿ������վ�Ĳ���
	std::vector<int> locsta;//���ڴ洢ÿ������վλ��
	std::vector<int> count;//��¼��ʼ�㵽ÿ������վ�ľ���
	int trans;//�ñ�����ʾ���ڵ�һ�������ԣ���Լ���վ��ƫת��
	int *min = new int(2000);
	for (size_t i = 0; i < sta.size(); i++)
	{
		if (*min > static_cast<int>(modify(((sta[i].GetLocation() - car1.GetLocation()) * car1.GetOrientation()) , car1.GetLength())))
		{
			trans = static_cast<int> (i);
			*min = static_cast<int>(modify(((sta[i].GetLocation() - car1.GetLocation()) * car1.GetOrientation()), car1.GetLength()));
			
		}
	}
	car1.trans = trans;
	car2.trans = trans;
	for (size_t i = 0; i < sta.size(); i++)
	{
		locsta.emplace_back(sta[i].GetLocation());
	}
	bool flag = true;
	int num = static_cast<int>(sta.size());
	bool car1sta, car2sta;
	do
	{//��Ҫ�ȼ��ͣ�������drive������
		//���һ������վ������
		auto min_value = popMinValue(count);
		//std::cout << "MIN_VALUE" << min_value.first << std::endl;
		//std::cout << "car_loc" << car.GetLocation() << std::endl;
		if (car1.Getx() == car1.GetLength() && car2.Getx() == car2.GetLength())
		{
			//std::cout << car.GetLength() << std::endl;
			break;
		}
		car1sta = CheckCarSta(car1, sta[modify(car1.trans , num)], car1.GetSpead());
		car2sta = CheckCarSta(car2, sta[modify(car2.trans , num)], car2.GetSpead());
		//std::cout << "trans" << car1.trans << std::endl;
		//std::cout << "trans" << car2.trans << std::endl;
		if (car1sta || car2sta)
		{
			bool car1getfuel = CarReplenishFuel(car1, sta[modify(car1.trans , num)], plan1[modify(car1.trans , num)], car1.GetSpead());
			bool car2getfuel = CarReplenishFuel(car2, sta[modify(car2.trans , num)], plan2[modify(car2.trans , num)], car2.GetSpead());
			if ( car1getfuel )
			{//������������
				//std::cout << min_value.first << " " << min_value.second << " " << sta[min_value.second].GetLocation() << std::endl;
				if (car1sta)
				{
					plan1[modify(car1.trans, num)] = 0;
					car1.trans += car1.GetOrientation();
				}
			}
			else
			{

				//std::cout << "�ƺ�����ͼ�ӳ�������վ��������" << std::endl;
				return Result::Fuelerror;
			}
			if (car2getfuel)
			{
				if (car2sta)
				{
					plan2[modify(car2.trans, num)] = 0;
					car2.trans += car2.GetOrientation();
				}
			}
			else
			{
				//std::cout << "�ƺ�����ͼ�ӳ�������վ��������" << std::endl;
				return Result::Fuelerror;
			}
			flag = car1.drive() && car2.drive();
		}
		else
		{
			flag = car1.drive() && car2.drive();
		}
		if (car1.Getx() % 5 == 0)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + y);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + y);
			Ground_load(PhaseLoop::DuringMainLoop, y);

			station_load(PhaseLoop::DuringMainLoop, 450 + y, locsta);

			Car1_load(PhaseLoop::DuringMainLoop, car1.GetLocation() + 450, 500 + y);
			Car1_load(PhaseLoop::DuringMainLoop, car2.GetLocation() + 450, 700 + y);
			al_flip_display();

			al_rest(0.05); // ��Ϣֱ����һ֡�Ŀ�ʼʱ��

		}
	} while (flag);//�����������
	if (flag == false)
	{
		//std::cout << "��Ǹ����������֧����ʻ��ȼ��" << std::endl;
		return Result::FuelLack;
	}
	else
	{
		//std::cout << "��ϲ������ͨ��" << std::endl;
		return Result::MissionACComplished;
	}
}
/// <summary>
/// �ú�����ģ�ⵥһ�����ø����ļ��ͷ���c���ڼ���վ�ֲ�b����ʻһȦ
/// </summary>
/// <param name="car"></param>
/// <param name="sta"></param>
/// <param name="plan"></param>
Result playCar(Car car, std::vector<GasStation> sta, std::vector<int> plan , int y)
{
	//�������ó��ӵ���ÿ������վ�Ĳ���
	std::vector<int> locsta;
	std::vector<int> count ;
	for (int i = 0; i < plan.size(); i++)
	{
		count.emplace_back(static_cast<int>((sta[i].GetLocation() - car.GetLocation()) / car.GetSpead() * car.GetOrientation() ));
		if (count[i] < 0 && car.GetOrientation() == 1)
		{
			count[i] += static_cast<int>(car.GetLength() / car.GetSpead());
		}
		else if (count[i] < 0 && car.GetOrientation() == -1)
		{
			count[i] += static_cast<int>(car.GetLength() / car.GetSpead());
		}
	}
	for (size_t i = 0; i < sta.size(); i++)
	{
		locsta.emplace_back(sta[i].GetLocation());
	}
	bool flag = true;
	do
	{//��Ҫ�ȼ��ͣ�������drive������
		//���һ������վ������
		auto min_value = popMinValue(count);
		//std::cout << "MIN_VALUE" << min_value.first << std::endl;
		//std::cout << "car_loc" << car.GetLocation() << std::endl;
		if (car.Getx() == car.GetLength())
		{
			//std::cout << car.GetLength() << std::endl;
			break;
		}
		if ((min_value.first == 0 || min_value.first == 1 || min_value.first == 2) && plan.size() )
		{
			if (CarReplenishFuel(car, sta[min_value.second] , plan[min_value.second], car.GetSpead() ) )
			{//������������
				//std::cout << min_value.first << " " << min_value.second << " " << sta[min_value.second].GetLocation() << std::endl;
				flag = car.drive(); 
				//::cout << "�Ѽ���" << plan[min_value.second] << "����ʻһ�Σ�λ��Ϊ: " << car.GetLocation() << std::endl;
				//std::cout << "ʣ��������" << car.GetFuel() << std::endl;
				if (count.size())
				{
					plan.erase(plan.begin() + min_value.second);
					sta.erase(sta.begin() + min_value.second);
					//std::cout << "yes?" << sta.size() << std::endl;
					for (size_t i = 0; i < count.size(); i++)
					{
						count[i] --;
					}
				}
			}
			else
			{
				//std::cout << "�ƺ�����ͼ�ӳ�������վ��������" << std::endl;
				return Result::Fuelerror;
			}
		}
		else
		{
			flag = car.drive();
			if (count.size())
			{
				for (size_t i = 0; i < count.size(); i++)
				{
					count[i] --;
				}
			}
		}
		if (car.Getx() % 5 ==0)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			Door_load(PhaseLoop::DuringMainLoop, 400, 650+y);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650+y);
			Ground_load(PhaseLoop::DuringMainLoop , y);

			station_load(PhaseLoop::DuringMainLoop, 450+y, locsta);

			Car1_load(PhaseLoop::DuringMainLoop, car.GetLocation() + 450, 500+y);
			al_flip_display();

			al_rest(0.05); // ��Ϣֱ����һ֡�Ŀ�ʼʱ��
			
		}
	}while (flag);//�����������
	if (flag == false)
	{
		//std::cout << "��Ǹ����������֧����ʻ��ȼ��" << std::endl;
		return Result::FuelLack;
	}
	else
	{
		//std::cout << "��ϲ������ͨ��" << std::endl;
		return Result::MissionACComplished;
	}
}
/// <summary>
/// �ú���ʵ�ֵ���������Сֵ
/// </summary>
/// <param name="vec"></param>
/// <returns></returns>
std::pair<int, int> popMinValue(std::vector<int>& vec) {
	// ʹ�� std::min_element �ҵ���Сֵ�ĵ�����
	auto min_element_iter = std::min_element(vec.begin(), vec.end());

	// �ж� min_element_iter �Ƿ���Ч����������������
	if (min_element_iter == vec.end()) {
		return { 10,10 };
	}
	// ��ȡ��Сֵ������
	int min_value = *min_element_iter;
	int index = std::distance(vec.begin(), min_element_iter);
	// �Ƴ���Сֵ
	if (min_value == 0 || min_value == 1 || min_value == 2)
	{
		vec.erase(min_element_iter);
	}
	// ������Сֵ
	return {min_value, index};
}
/// <summary>
/// �������غ���,��������ʱ������һ��š�
/// </summary>
void Car1_load(PhaseLoop phase , int x , int y)
{
	int NUM_FRAMES = 4;

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* frames[4];
		{for (int i = 0; i < NUM_FRAMES; ++i) {
			char filename[30]; // ����ʵ���ļ������ȵ���
			sprintf_s(filename, "Image/car-1/%d.png", i + 1); // �����ļ�����ʽΪ frame1.png, frame2.png, ..., frame30.png
			frames[i] = al_load_bitmap(filename);
		}
	}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Car_current_frame = 0;
		al_draw_bitmap(frames[Car_current_frame], x, y, 0); // �����Ͻǻ��Ƶ�ǰ֡��λͼ

		// �л�����һ֡
		++Car_current_frame;
		if (Car_current_frame >= NUM_FRAMES) {
			Car_current_frame = 0; // ѭ�����Ŷ���
		}
	}
		break;
	case PhaseLoop::AfterMainLoop:
		for (int i = 0; i < NUM_FRAMES; ++i) {
			al_destroy_bitmap(frames[i]);
		}
		break;
	default:
		//std::cout << "Unknown phase." << std::endl;
		break;
	}
	
}
void Car2_load(PhaseLoop phase, int x, int y)
{
	int NUM_FRAMES = 4;

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* frames[4];
		{
			for (int i = 0; i < NUM_FRAMES; ++i) {
				char filename[30]; // ����ʵ���ļ������ȵ���
				sprintf_s(filename, "Image/car1/%d.png", i + 1); // �����ļ�����ʽΪ frame1.png, frame2.png, ..., frame30.png
				frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Car_current_frame = 0;
		al_draw_bitmap(frames[Car_current_frame], x, y, 0); // �����Ͻǻ��Ƶ�ǰ֡��λͼ

		// �л�����һ֡
		++Car_current_frame;
		if (Car_current_frame >= NUM_FRAMES) {
			Car_current_frame = 0; // ѭ�����Ŷ���
		}
	}
	break;
	case PhaseLoop::AfterMainLoop:
		for (int i = 0; i < NUM_FRAMES; ++i) {
			al_destroy_bitmap(frames[i]);
		}
		break;
	default:
		//std::cout << "Unknown phase." << std::endl;
		break;
	}

}
void Query_load(PhaseLoop phase, int x, int y)
{
	int NUM_FRAMES = 10;

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* Query_frames[43];
		{
			for (int i = 0; i < NUM_FRAMES; ++i) {
				char filename[32]; // ����ʵ���ļ������ȵ���
				sprintf_s(filename, "Image/query/%d.png", i + 1); // �����ļ�����ʽΪ frame1.png, frame2.png, ..., frame30.png
				Query_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Quey_current_frame = 0;
		al_draw_bitmap(Query_frames[Quey_current_frame], x, y, 0); // �����Ͻǻ��Ƶ�ǰ֡��λͼ

		// �л�����һ֡
		++Quey_current_frame;
		if (Quey_current_frame >= NUM_FRAMES) {
			Quey_current_frame = 0; // ѭ�����Ŷ���
		}
	}
	break;
	case PhaseLoop::AfterMainLoop:
		for (int i = 0; i < NUM_FRAMES; ++i) {
			al_destroy_bitmap(Query_frames[i]);
		}
		break;
	default:
		break;
	}
}
void Star_load(PhaseLoop phase, int x, int y)
{
	int NUM_FRAMES = 11;

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* star_frames[43];
		{
			for (int i = 0; i < NUM_FRAMES; ++i) {
				char filename[32]; // ����ʵ���ļ������ȵ���
				sprintf_s(filename, "Image/star/%d.png", i + 1); // �����ļ�����ʽΪ frame1.png, frame2.png, ..., frame30.png
				star_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Star_current_frame = 0;
		al_draw_bitmap(star_frames[Star_current_frame], x, y, 0); // �����Ͻǻ��Ƶ�ǰ֡��λͼ

		// �л�����һ֡
		++Star_current_frame;
		if (Star_current_frame >= NUM_FRAMES) {
			Star_current_frame = 0; // ѭ�����Ŷ���
		}
	}
	break;
	case PhaseLoop::AfterMainLoop:
		for (int i = 0; i < NUM_FRAMES; ++i) {
			al_destroy_bitmap(star_frames[i]);
		}
		break;
	default:
		break;
	}
}
/// <summary>
/// �ܵ����غ���
/// </summary>
/// <param name="phase"></param>
void Ground_load(PhaseLoop phase , int y) 
{
	// ���幫·�Ķ�������
	float road_left_x = 500;
	float road_right_x = 1500;
	float road_top_y = 550+y;
	float road_bottom_y = 950+y;

	// �������±߽�İ�ɫʵ��
	al_draw_line(road_left_x, road_top_y, road_right_x, road_top_y, al_map_rgb(255, 255, 255), 20);    // �ϱ߽�
	al_draw_line(road_left_x, road_bottom_y, road_right_x, road_bottom_y, al_map_rgb(255, 255, 255), 20);  // �±߽�

	// �����м��˫����
	for (int x = road_left_x; x < road_right_x; x += 100) {
		al_draw_line(x, road_top_y + 200, x+50, road_top_y + 200, al_map_rgb(255, 255, 0), 10);  // ˫����
	}
}
/// <summary>
/// ����վ����
/// </summary>
/// <param name="phase"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void station_load(PhaseLoop phase, int y , std::vector<int> loc) 
{
	int NUM_FRAMES = loc.size();

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* station_frames;
		{
			char filename[30] = "Image/GasPump.png"; // ����ʵ���ļ������ȵ���
			station_frames = al_load_bitmap(filename);
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		for (size_t i = 0; i < NUM_FRAMES; i++)
		{
			
			al_draw_bitmap(station_frames, loc[i]+500, y, 0); // �����Ͻǻ��Ƶ�ǰ֡��λͼ
		}
	}
	break;
	case PhaseLoop::AfterMainLoop:
		al_destroy_bitmap(station_frames);
		break;
	default:
		//std::cout << "Unknown phase." << std::endl;
		break;
	}
}
void Door_load(PhaseLoop phase, int x, int y)
{
	int NUM_FRAMES = 25;

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* Door_frames[25];
		{
			for (int i = 0; i < NUM_FRAMES; ++i) {
				char filename[30]; // ����ʵ���ļ������ȵ���
				sprintf_s(filename, "Image/door/%d.png", i + 1); // �����ļ�����ʽΪ frame1.png, frame2.png, ..., frame30.png
				Door_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Door_current_frame = 0;
		al_draw_bitmap(Door_frames[Door_current_frame], x, y, 0); // �����Ͻǻ��Ƶ�ǰ֡��λͼ

		// �л�����һ֡
		++Door_current_frame;
		if (Door_current_frame >= NUM_FRAMES) {
			Door_current_frame = 0; // ѭ�����Ŷ���
		}
	}
	break;
	case PhaseLoop::AfterMainLoop:
		for (int i = 0; i < NUM_FRAMES; ++i) {
			al_destroy_bitmap(Door_frames[i]);
		}
		break;
	default:
		//std::cout << "Unknown phase." << std::endl;
		break;
	}
}


/// <summary>
/// �����������ѡ��ؿ��Լ���������
/// </summary>
bool game(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font)
{//���ҳ�棬Ȼ����ƹؿ���
	bool running = true;
	std::vector<LevelButton> levelbuttons = {
	 LevelButton(100, 100, 500, 200, font, "Please click" , "1"),
	 LevelButton(100, 300, 500, 400, font, "Please click" , "2"),
	 LevelButton(100, 500, 500, 600, font, "Please click" , "3"),
	 LevelButton(100, 700, 500, 800, font, "Please click" , "4"),
	 LevelButton(100, 900, 500, 1000, font, "Please click" , "5"),
	};
	FirstGameState state = FirstGameState::MAIN_MENU;
	bool redraw = true;
	bool close = true;
	
	while (running && state == FirstGameState::MAIN_MENU)
	{
		std::vector<std::function<bool(ALLEGRO_EVENT_QUEUE*, ALLEGRO_FONT*, FirstGameState&)>> levels = {level1 ,level2 , level3 , level4 , level5 };
		ALLEGRO_EVENT event;
		while (al_wait_for_event_timed(event_queue, &event, 0.01)) 
		{
			switch (event.type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return false;
				break;
			case ALLEGRO_EVENT_TIMER:
				redraw = true;
				break;
			default:
				break;
			}
			for (auto& levelbutton : levelbuttons) {
				levelbutton.handle_event(event);
			}
		}
		for (int i = 0; i < levelbuttons.size(); i++)
		{
			if (levelbuttons[i].click && state == FirstGameState::MAIN_MENU) 
			{
				levelbuttons[i].click = false;
				state = static_cast<FirstGameState>(i+1);
				close = levels[i](event_queue, font, state);
				redraw = true;
			}
		}
		if (redraw)
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(255, 255, 255));
			for (auto& levelbutton : levelbuttons) {
				levelbutton.draw();
			}
			Star_load(PhaseLoop::DuringMainLoop, 1000, 0);
			Car1_load(PhaseLoop::DuringMainLoop, 1000, 230);
			Car2_load(PhaseLoop::DuringMainLoop, 1000, 450);
			Query_load(PhaseLoop::DuringMainLoop, 1000, 680);
			Congratulation_load(PhaseLoop::DuringMainLoop, 1000, 910);
			// ����һС��ʱ�䣬����֡��
			al_flip_display();
			al_rest(0.1);

		}
	}
	return true;
}
// ���½�Ϊ�ؿ����ɺ���
// ��Ҫ������
// 1.���ɽ��棬���ɹؿ�
// 2.ָ��
// 3.�ȴ�����
// 4.����
// 5.չʾ���

/// <summary>
/// ��һ����򵥣�����������ȷ�λ�á�ȼ�ϵļ���վ
/// </summary>
/// <returns></returns>
bool level1(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font , FirstGameState &state)
{
	std::vector<InputBox> input_boxes = {
	 InputBox(100, 100, 500, 150, font, "Please 100", 0),
	 InputBox(100, 200, 500, 250, font, "Please 200,200,200,200,200",1)
	};
	std::vector<Car> car = CarGenerate(1, 2, 0, -1);
	std::vector<int> plan;
	std::vector<GasStation> sta;
	for (size_t i = 0; i < 5; i++)
	{
		sta.emplace_back(200, 100 + 200 * i);
	}
	std::vector<int> locsta;
	std::vector<std::string> INFORMATION;
	for (size_t i = 0; i < sta.size(); i++)
	{
		locsta.emplace_back(sta[i].GetLocation());
		INFORMATION.emplace_back(std::to_string(i)+"  Fuel: "+std::to_string(sta[i].GetFuel())+" , Location: "+std::to_string(sta[i].GetLocation()));
	}
	Car1_load(PhaseLoop::BeforeMainLoop, 0, 0);
	station_load(PhaseLoop::BeforeMainLoop, 0, locsta);
	Door_load(PhaseLoop::BeforeMainLoop, 0, 0);
	bool redraw = true;
	bool running1 = true;
	while (running1) {
		ALLEGRO_EVENT event;

		// �������ȴ��¼����ȴ�ʱ��Ϊ 0.01 ��
		while (al_wait_for_event_timed(event_queue, &event, 0.01)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				return false;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				running1 = false;
			}
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				running1 = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// ��������
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "I trust you can accomplish it ,my lord");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "If you have any question");
			al_draw_text(font, al_map_rgb(255, 255, 255), 500, 500, ALLEGRO_ALIGN_CENTER, "please read the quidbook file or look my video on bilibili!");
			al_draw_text(font, al_map_rgb(255, 255, 255), 600, 600, ALLEGRO_ALIGN_CENTER, "Press the Any key to continue");
			al_flip_display();
			redraw = false;
		}
	}
	while (state == FirstGameState::Level1_RUNNING)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		for (auto& input_box : input_boxes) {
			input_box.handle_event(event);
		}
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// once again, no game logic. fishy? maybe.
			redraw = true;
			break;
		}
		
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			state = FirstGameState::MAIN_MENU;
			break;
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return false;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for (auto& input_box : input_boxes) {
				input_box.draw();//���������
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//�����ֵ
			{
				int real_loc = loc - car[0].GetLocation();
				car[0].SetLocation(real_loc);
			}
			auto& plan = input_boxes[1].plan;
			if (plan.size() == sta.size())
			{
				Result res = playCar(car[0], sta, plan, 100);
				if (!GameState(event_queue, font, res, state)) 
				{
					
					return false;
				}
				plan.clear();
			}
		}
	}
}
/// <summary>
/// ���������������վ������ҡ�
/// </summary>
/// <param name="event_queue"></param>
/// <param name="font"></param>
/// <param name="state"></param>
/// <returns></returns>
bool level2(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState& state) {
	std::vector<InputBox> input_boxes = {
	 InputBox(100, 100, 500, 150, font, "Please input starting location", 0),
	 InputBox(100, 200, 500, 250, font, "Please input Fuelling plan",1)
	};
	std::vector<Car> car = CarGenerate(1, 2, 0, -1);
	std::vector<int> plan;
	auto sta = StationGenerate(3,1000,1000);
	std::vector<int> locsta;
	std::vector<std::string> INFORMATION;
	for (size_t i = 0; i < sta.size(); i++)
	{
		locsta.emplace_back(sta[i].GetLocation());
		INFORMATION.emplace_back(std::to_string(i) + "  Fuel: " + std::to_string(sta[i].GetFuel()) + " , Location: " + std::to_string(sta[i].GetLocation()));
	}
	Car1_load(PhaseLoop::BeforeMainLoop, 0, 0);
	station_load(PhaseLoop::BeforeMainLoop, 0, locsta);
	Door_load(PhaseLoop::BeforeMainLoop, 0, 0);
	bool redraw = true;
	bool running1 = true;
	while (running1) {
		ALLEGRO_EVENT event;

		// �������ȴ��¼����ȴ�ʱ��Ϊ 0.01 ��
		while (al_wait_for_event_timed(event_queue, &event, 0.01)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				return false;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				running1 = false;
			}
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				running1 = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// ��������
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Maybe you know how to set the location and plan");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "To make your car driving correctly");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 500, ALLEGRO_ALIGN_CENTER, "Now let us try some problem ,maybe it is harder");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 600, ALLEGRO_ALIGN_CENTER, "Press the Any key to continue");
			al_flip_display();
			redraw = false;
		}
	}
	while (state == FirstGameState::Level2_RUNNING)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		for (auto& input_box : input_boxes) {
			input_box.handle_event(event);
		}
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// once again, no game logic. fishy? maybe.
			redraw = true;
			break;
		}

		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			state = FirstGameState::MAIN_MENU;
			break;
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return false;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for (auto& input_box : input_boxes) {
				input_box.draw();//���������
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//�����ֵ
			{
				int real_loc = loc - car[0].GetLocation();
				car[0].SetLocation(real_loc);
			}
			auto& plan = input_boxes[1].plan;
			if (plan.size() == sta.size())
			{
				Result res = playCar(car[0], sta, plan, 100);
				if (!GameState(event_queue, font, res, state))
				{

					return false;
				}
				plan.clear();
			}
		}
	}
}
/// <summary>
/// ����ؿ��ǵ�����Ȼ������Ҿ�������һ������վ������
/// </summary>
/// <param name="event_queue"></param>
/// <param name="font"></param>
/// <param name="state"></param>
/// <returns></returns>
bool level3(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state) {
	std::vector<InputBox> input_boxes = {
	 InputBox(100, 100, 500, 150, font, "Please enter location", 0),
	};
	std::vector<Car> car = CarGenerate(1, 2, 0, -1);
	std::vector<int> plan;
	auto sta = StationGenerate(7, 1000, 1000);
	std::vector<int> locsta;
	std::vector<std::string> INFORMATION;
	for (size_t i = 0; i < sta.size(); i++)
	{
		locsta.emplace_back(sta[i].GetLocation());
		int fuel_loc = sta[i].GetLocation()-sta[modify(i-1,sta.size())].GetLocation();
		if (fuel_loc < 0)
		{
			fuel_loc += car[0].GetLength();
		}
		fuel_loc = sta[i].GetFuel() - fuel_loc;
		INFORMATION.emplace_back(std::to_string(i) + "  Fuel-dist: " + std::to_string(fuel_loc) + " , Location: " + std::to_string(sta[i].GetLocation()));
	}
	Car1_load(PhaseLoop::BeforeMainLoop, 0, 0);
	station_load(PhaseLoop::BeforeMainLoop, 0, locsta);
	Door_load(PhaseLoop::BeforeMainLoop, 0, 0);
	bool redraw = true;
	bool running1 = true;
	while (running1) {
		ALLEGRO_EVENT event;

		// �������ȴ��¼����ȴ�ʱ��Ϊ 0.01 ��
		while (al_wait_for_event_timed(event_queue, &event, 0.01)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				return false;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				running1 = false;
			}
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				running1 = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// ��������
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Maybe you find you just need to know the right start location");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "And fueling the all fuel when you meet one gasstation");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 500, ALLEGRO_ALIGN_CENTER, "Now let us try it");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 600, ALLEGRO_ALIGN_CENTER, "Press the Any key to continue");
			al_flip_display();
			redraw = false;
		}
	}
	while (state == FirstGameState::Level3_RUNNING)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		for (auto& input_box : input_boxes) {
			input_box.handle_event(event);
		}
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// once again, no game logic. fishy? maybe.
			redraw = true;
			break;
		}

		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			state = FirstGameState::MAIN_MENU;
			break;
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return false;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for (auto& input_box : input_boxes) {
				input_box.draw();//���������
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//�����ֵ
			{
				int real_loc = loc - car[0].GetLocation();
				car[0].SetLocation(real_loc);
			}
			std::vector<int> plan;
			for (size_t i = 0; i < sta.size(); i++)
			{
				plan.emplace_back(sta[i].GetFuel());
			}
			if (car[0].GetLocation() != 0)
			{
				Result res = playCar(car[0], sta, plan, 100);
				if (!GameState(event_queue, font, res, state))
				{
					return false;
				}
				plan.clear();
			}
		}
	}
}
bool level4(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state) {
	std::vector<InputBox> input_boxes = {
	 InputBox(100, 100, 500, 150, font, "Please input start loc", 0),
	 InputBox(100, 200, 500, 250, font, "Please enter fuel plan1",1),
	 InputBox(100, 300, 500, 350, font, "Please enter fuel plan2",1)
	};
	std::vector<Car> car = CarGenerate(2, 2, 0, -1);
	car[1].SetOrientation();
	std::vector<int> plan1, plan2;
	auto sta = StationGenerate(3, 1000, 2000);
	std::vector<int> locsta;
	std::vector<std::string> INFORMATION;
	for (size_t i = 0; i < sta.size(); i++)
	{
		locsta.emplace_back(sta[i].GetLocation());
		INFORMATION.emplace_back(std::to_string(i) + "  Fuel: " + std::to_string(sta[i].GetFuel()) + " , Location: " + std::to_string(sta[i].GetLocation()));
	}
	Car1_load(PhaseLoop::BeforeMainLoop, 0, 0);
	station_load(PhaseLoop::BeforeMainLoop, 0, locsta);
	Door_load(PhaseLoop::BeforeMainLoop, 0, 0);
	bool redraw = true;
	bool running1 = true;
	while (running1) {
		ALLEGRO_EVENT event;

		// �������ȴ��¼����ȴ�ʱ��Ϊ 0.01 ��
		while (al_wait_for_event_timed(event_queue, &event, 0.01)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				return false;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				running1 = false;
			}
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				running1 = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// ��������
			al_draw_text(font, al_map_rgb(255, 255, 255), 450, 300, ALLEGRO_ALIGN_CENTER, "In this level , you have to solve harder problem");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "There are two cars , and their direction is different");
			al_draw_text(font, al_map_rgb(255, 255, 255), 450, 500, ALLEGRO_ALIGN_CENTER, "Meanwhile their starting location is the same");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 600, ALLEGRO_ALIGN_CENTER, "Let us try it with 3 stations , it is easy ");
			al_draw_text(font, al_map_rgb(255, 255, 255), 450, 700, ALLEGRO_ALIGN_CENTER, "If you really are thinking");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 800, ALLEGRO_ALIGN_CENTER, "Press the Any key to continue");
			al_flip_display();
			redraw = false;
		}
	}
	while (state == FirstGameState::Level4_RUNNING)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		for (auto& input_box : input_boxes) {
			input_box.handle_event(event);
		}
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// once again, no game logic. fishy? maybe.
			redraw = true;
			break;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			state = FirstGameState::MAIN_MENU;
			break;
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return false;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for (auto& input_box : input_boxes) {
				input_box.draw();//���������
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			Car2_load(PhaseLoop::DuringMainLoop, car[1].GetLocation() + 450, 500 + 340);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//�����ֵ
			{
				int real_loc = loc - car[0].GetLocation();
				car[0].SetLocation(real_loc);
				car[1].SetLocation(real_loc);
			}
			auto& plan1 = input_boxes[1].plan;
			auto& plan2 = input_boxes[2].plan;
			if (plan1.size() == sta.size() && plan2.size() == sta.size())
			{
				Result res = playCar(car[0], car[1], sta, plan1, plan2, 100);
				if (!GameState(event_queue, font, res, state))
				{
					return false;
				}
				plan1.clear();
				plan2.clear();
			}
		}
	}
}
bool level5(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font, FirstGameState &state) {
	std::vector<InputBox> input_boxes = {
	 InputBox(100, 100, 500, 150, font, "Please input start loc", 0),
	 InputBox(100, 200, 500, 250, font, "Please enter fuel plan1",1),
	 InputBox(100, 300, 500, 350, font, "Please enter fuel plan2",1)
	};
	std::vector<Car> car = CarGenerate(2, 2, 0, -1);
	car[1].SetOrientation();
	std::vector<int> plan1, plan2;
	auto sta = StationGenerate(5,1000,2000);
	std::vector<int> locsta;
	std::vector<std::string> INFORMATION;
	for (size_t i = 0; i < sta.size(); i++)
	{
		locsta.emplace_back(sta[i].GetLocation());
		int fuel_loc = sta[i].GetLocation() - sta[modify(i - 1, sta.size())].GetLocation();
		if (fuel_loc < 0)
		{
			fuel_loc += car[0].GetLength();
		}
		fuel_loc = sta[i].GetFuel() - fuel_loc;
		INFORMATION.emplace_back(std::to_string(i) + "  Fuel-dist: " + std::to_string(fuel_loc) + " , Location: " + std::to_string(sta[i].GetLocation())+" , Fuel: "+ std::to_string(sta[i].GetFuel()));
	}
	Car1_load(PhaseLoop::BeforeMainLoop, 0, 0);
	station_load(PhaseLoop::BeforeMainLoop, 0, locsta);
	Door_load(PhaseLoop::BeforeMainLoop, 0, 0);
	bool redraw = true;
	bool running1 = true;
	while (running1) {
		ALLEGRO_EVENT event;

		// �������ȴ��¼����ȴ�ʱ��Ϊ 0.01 ��
		while (al_wait_for_event_timed(event_queue, &event, 0.01)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				return false;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				running1 = false;
			}
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				running1 = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// ��������
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Maybe this is a little difficult for you ");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "Please think carefully");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 500, ALLEGRO_ALIGN_CENTER, "Now let us try it");
			al_draw_text(font, al_map_rgb(255, 255, 255), 400, 600, ALLEGRO_ALIGN_CENTER, "Press the Any key to continue");
			al_flip_display();
			redraw = false;
		}
	}
	while (state == FirstGameState::Level5_RUNNING)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		for (auto& input_box : input_boxes) {
			input_box.handle_event(event);
		}
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// once again, no game logic. fishy? maybe.
			redraw = true;
			break;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			state = FirstGameState::MAIN_MENU;
			break;
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return false;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for (auto& input_box : input_boxes) {
				input_box.draw();//���������
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			Car2_load(PhaseLoop::DuringMainLoop, car[1].GetLocation() + 450, 500 + 340);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//�����ֵ
			{
				int real_loc = loc - car[0].GetLocation();
				car[0].SetLocation(real_loc);
				car[1].SetLocation(real_loc);
			}
			auto& plan1 = input_boxes[1].plan;
			auto& plan2 = input_boxes[2].plan;
			if (plan1.size() == sta.size() && plan2.size() == sta.size())
			{
				Result res = playCar(car[0], car[1], sta, plan1, plan2, 100);
				if (!GameState(event_queue, font, res, state))
				{
					return false;
				}
				plan1.clear();
				plan2.clear();
			}
		}
	}
}

/// <summary>
/// ��Ϣ���
/// </summary>
/// <param name="info"></param>
void InfoMenu(std::vector<std::string> info , ALLEGRO_FONT* font)
{
	float x1, y1;
	x1 = 1000;
	y1 = 100;
	std::string title = "INFORMATION";
	al_draw_rectangle(1000, 100, 1500, 200+70*info.size(), al_map_rgb(255,255, 255), 2);
	al_draw_text(font, al_map_rgb(255, 255, 255), x1 + 10, y1 + 10, 0, title.c_str());
	for (size_t i = 0; i < info.size(); i++)
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), x1 + 10, y1 + 90+50*i, 0, info[i].c_str());
	}
}

/// <summary>
/// ������һ����Ϸ����ʱ����ʾ�����Ϸ���
/// </summary>
/// <param name="event_queue"></param>
/// <param name="font"></param>
bool GameState(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font , Result &res , FirstGameState &state)
{
	ALLEGRO_EVENT event;
	bool redraw = true;
	bool running = true;
	
	while (running)
	{
		while (al_wait_for_event_timed(event_queue, &event, 0.01)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
				return false;
			}//720, 660, 930, 690
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.x >= 720 && event.mouse.x <= 930 && event.mouse.y >= 660 && event.mouse.y <= 690) {
				state = FirstGameState::MAIN_MENU;
				return true;

			}
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.x >= 1020 && event.mouse.x <= 1230 && event.mouse.y >= 660 && event.mouse.y <= 690)
			{
				return true;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					running = false;
					break;
				}
			}
		}
		if (redraw)
		{
			redraw = false;
			//800,550,1200,900
			al_draw_filled_rectangle(700, 350, 1300, 700, al_map_rgb(125, 255, 255));
			switch (res)
			{
			case Result::FuelLack:
				Query_load(PhaseLoop::DuringMainLoop, 880, 390);
				al_draw_text(font, al_map_rgb(0, 0, 0), 850, 370, 0, "Thought Lose : Fuel  Lack");
				break;
			case Result::Fuelerror:
				Query_load(PhaseLoop::DuringMainLoop, 880, 390);
				al_draw_text(font, al_map_rgb(0, 0, 0), 850, 370, 0, "Thought Lose : The station dont have enough fule");
				break;
			case Result::MissionACComplished:
				al_draw_text(font, al_map_rgb(0, 0, 0), 850, 370, 0, "Thought Accomplished : Congratulation!");
				Congratulation_load(PhaseLoop::DuringMainLoop, 880, 400);
				break;
			default:
				break;
			}
			al_draw_rectangle(720, 660, 930, 690, al_map_rgb(255, 0, 255), 3);
			al_draw_rectangle(1020, 660, 1230, 690, al_map_rgb(255, 0, 255), 3);
			al_draw_text(font, al_map_rgb(0, 0, 0), 730, 665, 0, "Return Main Menu");
			al_draw_text(font, al_map_rgb(0, 0, 0), 1030, 665, 0, "Remake this level");
			
			al_flip_display();
			al_rest(0.1);
		}	
	}
}
void Congratulation_load(PhaseLoop phase, int x, int y)
{
	int NUM_FRAMES = 43;

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* Congratulation_frames[43];
		{
			for (int i = 0; i < NUM_FRAMES; ++i) {
				char filename[32]; // ����ʵ���ļ������ȵ���
				sprintf_s(filename, "Image/Congratulation/%d.png", i + 1); // �����ļ�����ʽΪ frame1.png, frame2.png, ..., frame30.png
				Congratulation_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Cgratulation_current_frame = 0;
		al_draw_bitmap(Congratulation_frames[Cgratulation_current_frame], x, y, 0); // �����Ͻǻ��Ƶ�ǰ֡��λͼ

		// �л�����һ֡
		++Cgratulation_current_frame;
		if (Cgratulation_current_frame >= NUM_FRAMES) {
			Cgratulation_current_frame = 0; // ѭ�����Ŷ���
		}
	}
	break;
	case PhaseLoop::AfterMainLoop:
		for (int i = 0; i < NUM_FRAMES; ++i) {
			al_destroy_bitmap(Congratulation_frames[i]);
		}
		break;
	default:
		break;
	}

}
