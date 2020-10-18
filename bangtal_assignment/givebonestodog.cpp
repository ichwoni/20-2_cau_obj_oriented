#include <bangtal.h>
using namespace bangtal;

class Rect {
public:
	int centerX, centerY;
	int radius;

	Rect(int cx, int cy, int r) : centerX(cx), centerY(cy), radius(r) {};
	
	bool checkIn(int x, int y) const {
		return (x > centerX - radius && x < centerX + radius && y > centerY - radius && y < centerY + radius);
	}
};

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	auto bones_count = 0;

	auto scene_main = Scene::create("", "img/main(1).png");
	auto scene_final = Scene::create("", "img/main.png");

	auto scene_r1 = Scene::create("1 round", "img/spotdifference01.png");
	auto problem_r1 = Object::create("img/spotdifference01.png", scene_r1, 0, 0);

	auto scene_r2 = Scene::create("2 round", "img/spotdifference01.png");
	auto problem_r2 = Object::create("img/spotdifference02.png", scene_r2, 0, 0);

	auto scene_r3 = Scene::create("3 round", "img/spotdifference01.png");
	auto problem_r3 = Object::create("img/spotdifference03.png", scene_r3, 0, 0);
	
	auto explain = Object::create("img/explain.png", scene_main, 680, 400);
	explain->setScale(0.2f);
	auto start = Object::create("img/start.png", scene_main, 700, 150);
	start->setScale(0.2f);

	auto next_r1 = Object::create("img/next.png", scene_r1, 980, 50);
	next_r1->setScale(0.2f);
	auto next_r2 = Object::create("img/next.png", scene_r2, 980, 50);
	next_r2->setScale(0.2f);
	auto finish = Object::create("img/finish.png", scene_r3, 980, 50);
	finish->setScale(0.2f);

	auto bones_1 = Object::create("img/bone.png", scene_final, 700, 200, false);
	bones_1->setScale(0.2f);
	auto bones_2 = Object::create("img/bone.png", scene_final, 730, 200, false);
	bones_2->setScale(0.2f);
	auto bones_3 = Object::create("img/bone.png", scene_final, 760, 200, false);
	bones_3->setScale(0.2f);

		
	start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_r1->enter();
		return true;
		});

	next_r1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_r2->enter();
		return true;
		});

	next_r2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_r3->enter();
		return true;
		});

	finish->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_final->enter();

		if (bones_count == 0) {
			showMessage("간식을 하나도 못 받았지만 괜찮아요!");
		}

		else if (bones_count == 1) {
			showMessage("간식을 하나만 받았지만 너무 맛있어요!");
			bones_1->show();
		}

		else if (bones_count <= 3) {
			showMessage("간식을 많이 받아서 기분이 좋아요!");
			if (bones_count == 2) {
				bones_1->show();
				bones_2->show();
			}
			else if (bones_count == 3) {
				bones_1->show();
				bones_2->show();
				bones_3->show();
			}
		}

		return true;
		});


	const int num_of_differences = 5;

	Rect up_rects_r1[num_of_differences] = {
		{ 410, 210, 50 },
		{ 450, 290, 50 },
		{ 530, 100, 50 },
		{ 550, 390, 50 },
		{ 570, 290, 50 },
	};

	Rect down_rects_r1[num_of_differences] = {
		{ 450, 230, 50 },
		{ 550, 0, 50 },
		{ 670, 100, 50 },
		{ 690, 390, 50 },
		{ 570, 290, 50 },
	};

	const int check_size = 25;
	ObjectPtr up_checks[num_of_differences];
	ObjectPtr down_checks[num_of_differences];

	for (int i = 0; i < num_of_differences; ++i) {
		up_checks[i] = Object::create("img/check.png", scene_r1, up_rects_r1[i].centerX - check_size, up_rects_r1[i].centerY - check_size, false);
		down_checks[i] = Object::create("img/check.png", scene_r1, down_rects_r1[i].centerX - check_size, down_rects_r1[i].centerY - check_size, false);
	}

	auto count = 0;

	problem_r1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bool checked = true;
		for (auto i = 0; i < num_of_differences; ++i) {
			if (up_rects_r1[i].checkIn(x, y) || down_rects_r1[i].checkIn(x, y)) {
				//up_checks[i]->show();
				down_checks[i]->show();
				checked = true;
				count++;
			}
		}

		if (checked == false) {
			showMessage(" ");
		}

		if (count == num_of_differences) {
			showMessage("간식 하나 추가!");
			bones_count++;
		}

		return true;
		});

	/*
	problem_r2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bool checked = true;
		for (auto i = 0; i < num_of_differences; ++i) {
			if (up_rects[i].checkIn(x, y) || down_rects[i].checkIn(x, y)) {
				up_checks[i]->show();
				down_checks[i]->show();
				checked = true;
				count++;
			}
		}

		if (checked == false) {
			showMessage(" ");
		}

		if (count == num_of_differences) {
			showMessage("간식 하나 추가!");
			bones_count++;
		}

		return true;
		});

	problem_r3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bool checked = true;
		for (auto i = 0; i < num_of_differences; ++i) {
			if (up_rects[i].checkIn(x, y) || down_rects[i].checkIn(x, y)) {
				up_checks[i]->show();
				down_checks[i]->show();
				checked = true;
				count++;
			}
		}

		if (checked == false) {
			showMessage(" ");
		}

		if (count == num_of_differences) {
			showMessage("간식 하나 추가!");
			bones_count++;
		}

		return true;
		});*/

	startGame(scene_main);

	return 0;
}