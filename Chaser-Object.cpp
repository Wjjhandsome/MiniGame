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
/// 给车加或者减燃料
/// </summary>
/// <param name="fue"></param>
void Car::SetFuel(int fue)
{
	fuel += fue;
}
/// <summary>
/// 获取车辆当前燃料并返回
/// </summary>
/// <returns></returns>
int Car::GetFuel() const 
{
	return fuel;
}
/// <summary>
/// 获取车辆速度并返回
/// </summary>
/// <returns>int</returns>
int Car::GetSpead() const 
{ 
	return spead;
}
/// <summary>
/// 设置车辆速度
/// </summary>
/// <param name="spea"></param>
void Car::SetSpead(int spea) 
{
	spead += spea;
}
/// <summary>
/// 初始化车辆的燃料、速度、位置、朝向、总行程。
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
/// 移动汽车
/// </summary>
/// <param name="loc"></param>
void Car::SetLocation(int loc)
{
	location += loc;
}
/// <summary>
/// 获取汽车当前位置
/// </summary>
/// <returns></returns>
int Car::GetLocation() const
{
	return location;
}
/// <summary>
/// 行驶函数，自动对环形跑道取模，返回false说明没有燃料支持继续跑了。
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
/// 反转车的方向
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
/// 给加油站减燃料
/// </summary>
/// <param name="fue"></param>
void GasStation::SetFuel(int fue)
{
	fuel += fue;
}
/// <summary>
/// 获取加油站当前燃料并返回
/// </summary>
/// <returns></returns>
int GasStation::GetFuel() const
{
	return fuel;
}

/// <summary>
/// 设置加油站位置
/// </summary>
/// <param name="loc"></param>
void GasStation::SetLocation(int loc)
{
	location += loc;
}
/// <summary>
/// 获取加油站当前位置
/// </summary>
/// <returns></returns>
int GasStation::GetLocation() const
{
	return location;
}
/// <summary>
/// 返回加油站油量是否合乎标准
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
/// 获取跑道长度.
/// </summary>
/// <returns></returns>
int Ground::GetLength()
{
	return length;
}
int modify(int a, int b)
{
	int result = a % b;
	// 如果 result 是负数，则加上 b 的绝对值
	if (result < 0) {
		result += std::abs(b);
	}
	return result;
}
/// <summary>
/// 检查车与加油站在误差范围内是否在同一地点
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
/// 批量生成车辆对象，c为个数，spea为速度，loc为初始位置
/// </summary>
/// <param name="c"></param>
/// <param name="spea"></param>
/// <param name="loc"></param>
std::vector<Car> CarGenerate(int c, int spea, int loc , int orien)
{
	std::vector<Car> objects;
	for (int i = 0; i < c; ++i) {
		objects.emplace_back(0 , spea , loc , orien , 0); // 使用 emplace_back 直接构造对象
	}
	return objects;
}
/// <summary>
/// len为总长度，c为加油站个数，sum为油量总和，n为数据需要保留多少小数。
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
/// 实现汽车在加油站加油，是否应该在汽车对象里面录入加油站名单，若在某一时刻loc大于他了，就加油
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
/// 该函数用于生成大小为c的保留n位小数数组，其和为a，k值表示是否需要总和为a
/// </summary>
/// <param name="c"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="k"></param>
/// <returns></returns>
std::vector<int> generateRandomArray(int c , int a , bool k) {
	std::vector<int> array(c);
	// 初始化随机数生成器
	//要取得[a, b) 的随机整数，使用(rand() % (b - a)) + a;
	//要取得[a, b] 的随机整数，使用(rand() % (b - a + 1)) + a;
	//要取得(a, b] 的随机整数，使用(rand() % (b - a)) + a + 1;
	std::srand(static_cast<unsigned int>(std::time(0)));
	// 生成随机浮点数
	for (int i = 0; i < c; ++i) {
		int value = static_cast<int>((std::rand() % (a+1)))  ;
		array[i] = value;
	}
	// 计算当前数组元素的总和
	if (k)
	{
		int currentSum = std::accumulate(array.begin(), array.end(), 0);
		// 计算调整比例
		double scale = static_cast<double>(a) / currentSum;
		// 调整数组元素以使其总和为 a
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
	//事先做好车子到达每个加油站的步数
	std::vector<int> locsta;//用于存储每个加油站位置
	std::vector<int> count;//记录起始点到每个加油站的距离
	int trans;//该变量表示对于第一辆车而言，其对加油站的偏转量
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
	{//需要先加油，再运行drive函数，
		//最后一个加油站有问题
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
			{//索引出了问题
				//std::cout << min_value.first << " " << min_value.second << " " << sta[min_value.second].GetLocation() << std::endl;
				if (car1sta)
				{
					plan1[modify(car1.trans, num)] = 0;
					car1.trans += car1.GetOrientation();
				}
			}
			else
			{

				//std::cout << "似乎你企图加超过加油站油量的油" << std::endl;
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
				//std::cout << "似乎你企图加超过加油站油量的油" << std::endl;
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

			al_rest(0.05); // 休息直到下一帧的开始时间

		}
	} while (flag);//这里很有问题
	if (flag == false)
	{
		//std::cout << "抱歉，车辆已无支持行驶的燃料" << std::endl;
		return Result::FuelLack;
	}
	else
	{
		//std::cout << "恭喜，您已通关" << std::endl;
		return Result::MissionACComplished;
	}
}
/// <summary>
/// 该函数将模拟单一车辆用给定的加油方案c，在加油站分布b上行驶一圈
/// </summary>
/// <param name="car"></param>
/// <param name="sta"></param>
/// <param name="plan"></param>
Result playCar(Car car, std::vector<GasStation> sta, std::vector<int> plan , int y)
{
	//事先做好车子到达每个加油站的步数
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
	{//需要先加油，再运行drive函数，
		//最后一个加油站有问题
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
			{//索引出了问题
				//std::cout << min_value.first << " " << min_value.second << " " << sta[min_value.second].GetLocation() << std::endl;
				flag = car.drive(); 
				//::cout << "已加油" << plan[min_value.second] << "，行驶一次，位置为: " << car.GetLocation() << std::endl;
				//std::cout << "剩余油量：" << car.GetFuel() << std::endl;
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
				//std::cout << "似乎你企图加超过加油站油量的油" << std::endl;
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

			al_rest(0.05); // 休息直到下一帧的开始时间
			
		}
	}while (flag);//这里很有问题
	if (flag == false)
	{
		//std::cout << "抱歉，车辆已无支持行驶的燃料" << std::endl;
		return Result::FuelLack;
	}
	else
	{
		//std::cout << "恭喜，您已通关" << std::endl;
		return Result::MissionACComplished;
	}
}
/// <summary>
/// 该函数实现弹出数组最小值
/// </summary>
/// <param name="vec"></param>
/// <returns></returns>
std::pair<int, int> popMinValue(std::vector<int>& vec) {
	// 使用 std::min_element 找到最小值的迭代器
	auto min_element_iter = std::min_element(vec.begin(), vec.end());

	// 判断 min_element_iter 是否有效，避免空向量的情况
	if (min_element_iter == vec.end()) {
		return { 10,10 };
	}
	// 获取最小值及索引
	int min_value = *min_element_iter;
	int index = std::distance(vec.begin(), min_element_iter);
	// 移除最小值
	if (min_value == 0 || min_value == 1 || min_value == 2)
	{
		vec.erase(min_element_iter);
	}
	// 返回最小值
	return {min_value, index};
}
/// <summary>
/// 车辆加载函数,两个车的时候，上下一起放。
/// </summary>
void Car1_load(PhaseLoop phase , int x , int y)
{
	int NUM_FRAMES = 4;

	switch (phase)
	{
	case PhaseLoop::BeforeMainLoop:
		static ALLEGRO_BITMAP* frames[4];
		{for (int i = 0; i < NUM_FRAMES; ++i) {
			char filename[30]; // 根据实际文件名长度调整
			sprintf_s(filename, "Image/car-1/%d.png", i + 1); // 假设文件名格式为 frame1.png, frame2.png, ..., frame30.png
			frames[i] = al_load_bitmap(filename);
		}
	}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Car_current_frame = 0;
		al_draw_bitmap(frames[Car_current_frame], x, y, 0); // 在左上角绘制当前帧的位图

		// 切换到下一帧
		++Car_current_frame;
		if (Car_current_frame >= NUM_FRAMES) {
			Car_current_frame = 0; // 循环播放动画
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
				char filename[30]; // 根据实际文件名长度调整
				sprintf_s(filename, "Image/car1/%d.png", i + 1); // 假设文件名格式为 frame1.png, frame2.png, ..., frame30.png
				frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Car_current_frame = 0;
		al_draw_bitmap(frames[Car_current_frame], x, y, 0); // 在左上角绘制当前帧的位图

		// 切换到下一帧
		++Car_current_frame;
		if (Car_current_frame >= NUM_FRAMES) {
			Car_current_frame = 0; // 循环播放动画
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
				char filename[32]; // 根据实际文件名长度调整
				sprintf_s(filename, "Image/query/%d.png", i + 1); // 假设文件名格式为 frame1.png, frame2.png, ..., frame30.png
				Query_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Quey_current_frame = 0;
		al_draw_bitmap(Query_frames[Quey_current_frame], x, y, 0); // 在左上角绘制当前帧的位图

		// 切换到下一帧
		++Quey_current_frame;
		if (Quey_current_frame >= NUM_FRAMES) {
			Quey_current_frame = 0; // 循环播放动画
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
				char filename[32]; // 根据实际文件名长度调整
				sprintf_s(filename, "Image/star/%d.png", i + 1); // 假设文件名格式为 frame1.png, frame2.png, ..., frame30.png
				star_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Star_current_frame = 0;
		al_draw_bitmap(star_frames[Star_current_frame], x, y, 0); // 在左上角绘制当前帧的位图

		// 切换到下一帧
		++Star_current_frame;
		if (Star_current_frame >= NUM_FRAMES) {
			Star_current_frame = 0; // 循环播放动画
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
/// 跑道加载函数
/// </summary>
/// <param name="phase"></param>
void Ground_load(PhaseLoop phase , int y) 
{
	// 定义公路的顶点坐标
	float road_left_x = 500;
	float road_right_x = 1500;
	float road_top_y = 550+y;
	float road_bottom_y = 950+y;

	// 绘制上下边界的白色实线
	al_draw_line(road_left_x, road_top_y, road_right_x, road_top_y, al_map_rgb(255, 255, 255), 20);    // 上边界
	al_draw_line(road_left_x, road_bottom_y, road_right_x, road_bottom_y, al_map_rgb(255, 255, 255), 20);  // 下边界

	// 绘制中间的双黄线
	for (int x = road_left_x; x < road_right_x; x += 100) {
		al_draw_line(x, road_top_y + 200, x+50, road_top_y + 200, al_map_rgb(255, 255, 0), 10);  // 双黄线
	}
}
/// <summary>
/// 加油站函数
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
			char filename[30] = "Image/GasPump.png"; // 根据实际文件名长度调整
			station_frames = al_load_bitmap(filename);
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		for (size_t i = 0; i < NUM_FRAMES; i++)
		{
			
			al_draw_bitmap(station_frames, loc[i]+500, y, 0); // 在左上角绘制当前帧的位图
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
				char filename[30]; // 根据实际文件名长度调整
				sprintf_s(filename, "Image/door/%d.png", i + 1); // 假设文件名格式为 frame1.png, frame2.png, ..., frame30.png
				Door_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Door_current_frame = 0;
		al_draw_bitmap(Door_frames[Door_current_frame], x, y, 0); // 在左上角绘制当前帧的位图

		// 切换到下一帧
		++Door_current_frame;
		if (Door_current_frame >= NUM_FRAMES) {
			Door_current_frame = 0; // 循环播放动画
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
/// 这个函数控制选择关卡以及后续操作
/// </summary>
bool game(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font)
{//清除页面，然后绘制关卡。
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
			// 休眠一小段时间，控制帧率
			al_flip_display();
			al_rest(0.1);

		}
	}
	return true;
}
// 以下皆为关卡生成函数
// 需要包含：
// 1.生成界面，生成关卡
// 2.指引
// 3.等待输入
// 4.运行
// 5.展示结果

/// <summary>
/// 第一关最简单，单车，五个等分位置、燃料的加油站
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

		// 软阻塞等待事件，等待时间为 0.01 秒
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

			// 绘制内容
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
				input_box.draw();//绘制输入框
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//赋予初值
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
/// 用随机的三个加油站测试玩家。
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

		// 软阻塞等待事件，等待时间为 0.01 秒
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

			// 绘制内容
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
				input_box.draw();//绘制输入框
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//赋予初值
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
/// 这个关卡是单车，然后让玩家决定在哪一个加油站出发，
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

		// 软阻塞等待事件，等待时间为 0.01 秒
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

			// 绘制内容
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
				input_box.draw();//绘制输入框
			}
			Door_load(PhaseLoop::DuringMainLoop, 400, 650 + 100);
			Door_load(PhaseLoop::DuringMainLoop, 1400, 650 + 100);
			Ground_load(PhaseLoop::DuringMainLoop, 100);
			InfoMenu(INFORMATION, font);
			station_load(PhaseLoop::DuringMainLoop, 450 + 100, locsta);
			Car1_load(PhaseLoop::DuringMainLoop, car[0].GetLocation() + 450, 500 + 100);
			al_flip_display();
			int loc = input_boxes[0].loc;
			if (car[0].GetLocation() != loc)//赋予初值
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

		// 软阻塞等待事件，等待时间为 0.01 秒
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

			// 绘制内容
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
				input_box.draw();//绘制输入框
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
			if (car[0].GetLocation() != loc)//赋予初值
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

		// 软阻塞等待事件，等待时间为 0.01 秒
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

			// 绘制内容
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
				input_box.draw();//绘制输入框
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
			if (car[0].GetLocation() != loc)//赋予初值
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
/// 信息面板
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
/// 用于在一轮游戏结束时，提示玩家游戏结果
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
				char filename[32]; // 根据实际文件名长度调整
				sprintf_s(filename, "Image/Congratulation/%d.png", i + 1); // 假设文件名格式为 frame1.png, frame2.png, ..., frame30.png
				Congratulation_frames[i] = al_load_bitmap(filename);
			}
		}
		break;
	case PhaseLoop::DuringMainLoop:
	{
		static int Cgratulation_current_frame = 0;
		al_draw_bitmap(Congratulation_frames[Cgratulation_current_frame], x, y, 0); // 在左上角绘制当前帧的位图

		// 切换到下一帧
		++Cgratulation_current_frame;
		if (Cgratulation_current_frame >= NUM_FRAMES) {
			Cgratulation_current_frame = 0; // 循环播放动画
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
