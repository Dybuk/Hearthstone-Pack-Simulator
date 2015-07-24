/*
* @Author
* Author Name: Bishey
* Date of completion: 17.11.2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <string.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int total_common, total_rare, total_epic, total_legendary, total_gold_common, total_gold_rare, total_gold_epic, total_gold_legendary = 0;
int inpack_common, inpack_rare, inpack_epic, inpack_legendary, inpack_gold_common, inpack_gold_rare, inpack_gold_epic, inpack_gold_legendary = 0;
int packs_opened = 0;
int dust = 0;

//Default Collection - Start
int common_card_no = 47;
int rare_card_no = 40;
int epic_card_no = 19;
int legendary_card_no = 17;

vector<int> common_collection(common_card_no);
vector<int> rare_collection(rare_card_no);
vector<int> epic_collection(epic_card_no);
vector<int> legendary_collection(legendary_card_no);

vector<int> gold_common_collection(common_card_no);
vector<int> gold_rare_collection(rare_card_no);
vector<int> gold_epic_collection(epic_card_no);
vector<int> gold_legendary_collection(legendary_card_no);
//Default Collection - End

float common_percentage = 70;
float rare_percentage = 21.39;
float epic_percentage = 4.28;
float legendary_percentage = 1.08;

float gold_common_percentage = 1.469;
float gold_rare_percentage = 1.37;
float gold_epic_percentage = 0.308;
float gold_legendary_percentage = 0.103;

int common_chance, rare_chance, epic_chance, legendary_chance, gold_common_chance, gold_rare_chance, gold_epic_chance, gold_legendary_chance;

int dust_created = 0;
int gold_dust_created = 0;

int legendaries_crafted = 0;
int epics_crafted = 0;
int rares_crafted = 0;
int commons_crafted = 0;

int gold_legendaries_crafted = 0;
int gold_epics_crafted = 0;
int gold_rares_crafted = 0;
int gold_commons_crafted = 0;

int comp_leg = 0;
int comp_epic = 0;
int half_epic = 0;
int comp_rare = 0;
int half_rare = 0;
int comp_com = 0;
int half_com = 0;

int comp_gold_leg = 0;
int comp_gold_epic = 0;
int half_gold_epic = 0;
int comp_gold_rare = 0;
int half_gold_rare = 0;
int comp_gold_com = 0;
int half_gold_com = 0;

bool reg_collection_finished = false;
bool gold_collection_finished = false;

bool de_one_third = false;

int reg_collection_finished_packs = 0;
int gold_collection_finished_packs = 0;

int avg_reg_pack = 0;
int min_reg_pack = 99999999;
int max_reg_pack = 0;

int avg_gold_pack = 0;

bool reg_notification = false;
bool gold_notification = false;

void print_menu();
bool operate(char);
void create_collection();
void open_x_packs(int);
void show_progress();
void calculate_progress();
void show_collection();
void finish_collection();
void finish_collection_no_gold();
void finish_multiple_collection();
void finish_multiple_collection_no_gold();
void craft_regular_collection();
void craft_regular_collection_use_all_dust();
void craft_gold_collection();
void craft_gold_collection_use_all_dust();
void open_pack();
void disenchant_extras();
void disenchant_gold_cards();
void convert_percentage();
void show_percentage();
void check_completion();
void reset_program();

int main(){
	bool terminate = false;
	char choice;
	srand(time(NULL));
	cout << endl;
	cout << "Welcome to the Hearthstone Pack Simulator. This software is designed to" << endl;
	cout << "open packs and calculate the amount of packs needed to complete a given" << endl;
	cout << "collection. It can calculate separate values for a regular and a golden" << endl;
	cout << "collection. It can also use the dust that you get from extra cards." << endl << endl;
	cout << "This software is created by Bishey (u/bishey3)" << endl << endl;
	system("Pause");
	create_collection();
	cout << endl;
	system("Pause");
	convert_percentage();
	while (terminate == false) {
		print_menu();
		cin >> choice;
		terminate = operate(choice);
		cout << endl;
		system("Pause");
	}
	return EXIT_SUCCESS;
}

void print_menu(){
	system("cls");
	cout << endl;
	cout << "           Hearthstone Pack Simulator" << endl;
	cout << endl << "--------------------------------------------------" << endl << endl;
	cout << "Packs Opened: " << packs_opened << " - Dust: " << dust << endl << endl;
	cout << "0: Reset the program" << endl;
	cout << "1: View or change the collection" << endl;
	cout << "2: View or change the percentages of card drops" << endl;
	cout << "3: Open packs" << endl;
	cout << "4: Disenchant cards" << endl;
	cout << "5: Craft cards" << endl;
	cout << "6: Show collection progress" << endl;
	cout << "7: Complete the collection" << endl;
	cout << "8: Calculate average packs to complete collection" << endl;
	cout << "9: Exit" << endl << endl;
	cout << "Please enter your option (0 - 9): ";
}

bool operate(char choice){
	bool terminate = false;
	switch (choice) {
	case '0':
		system("cls");
		cout << endl << "Warning: Reseting the program will erase all progress so far! (Duh)" << endl << endl;
		cout << "Reset the progress? (Y/N): ";
		char choice6;
		cin >> choice6;
		cin.ignore(1024, '\n');
		switch (choice6){
		case 'Y': case'y':
			reset_program();
			break;
		default:
			break;
		}
		break;
	case '1':
		system("cls");
		show_collection();
		cout << endl << "Warning: Changing the collection will erase all progress so far!" << endl << endl;
		cout << "Change the collection? (Y/N): ";
		char choice3;
		cin >> choice3;
		cin.ignore(1024, '\n');
		switch (choice3){
			case 'Y': case'y':
				reset_program();
				create_collection();
				break;
			default:
				break;
		}
		break;
	case '2':
		system("cls");
		show_percentage();
		convert_percentage();
		break;
	case '3':
		system("cls");
		cout << endl << "How many packs you would like to open." << endl << endl;
		cout << "Please enter a number: ";
		int x;
		cin >> x;
		open_x_packs(x);
		break;
	case '4':
		system("cls");
		cout << endl << "1. Disenchant extra cards" << endl;
		cout << "2. Disenchant extra cards and all golden cards" << endl << endl;
		cout << "Choose an option (1, 2): ";
		char choice7;
		cin >> choice7;
		cin.ignore(1024, '\n');
		switch (choice7){
		case '1':
			disenchant_extras();
			break;
		case '2':
			disenchant_extras();
			disenchant_gold_cards();
			break;
		default:
			break;
		}
		cout << endl << "Extra cards were disenchanted into dust." << endl;
		cout << endl << "Created Dust : " << (dust_created + gold_dust_created) << endl;
		break;
	case '5':
		system("Cls");
		cout << endl << "1. Craft regular cards" << endl;
		cout << "2. Craft golden cards" << endl << endl;
		cout << "Choose an option (1, 2): ";
		char choice10;
		cin >> choice10;
		cin.ignore(1024, '\n');
		switch (choice10){
		case '1':
			system("Cls");
			cout << endl << "Current Dust : " << dust << endl;
			cout << endl << "1. Use all dust available." << endl;
			cout << "2. Prioritise higher rarity cards." << endl << endl;
			cout << "Choose an option (1, 2): ";
			char choice5;
			cin >> choice5;
			cin.ignore(1024, '\n');
			switch (choice5){
			case '1':
				craft_regular_collection_use_all_dust();
				break;
			case '2':
				craft_regular_collection();
				break;
			default:
				break;
			}
			cout << endl << commons_crafted << " Commons crafted." << endl;
			cout << endl << rares_crafted << " Rares crafted." << endl;
			cout << endl << epics_crafted << " Epics crafted." << endl;
			cout << endl << legendaries_crafted << " Legendaries crafted." << endl;
			calculate_progress();
			check_completion();
			if (reg_collection_finished == true && reg_notification == false){
				cout << endl;
				system("Pause");
				system("cls");
				cout << "Congratulations! You just completed the regular collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				reg_notification = true;
			}
			if (gold_collection_finished == true && gold_notification == false){
				cout << endl;
				system("Pause");
				system("cls");
				cout << "Congratulations! You just completed the GOLDEN collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Totally Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				gold_notification = true;
			}
			break;
		case '2':
			system("Cls");
			cout << endl << "Current Dust : " << dust << endl;
			cout << endl << "1. Use all dust available." << endl;
			cout << "2. Prioritise higher rarity cards." << endl << endl;
			cout << "Choose an option (1, 2): ";
			char choice11;
			cin >> choice11;
			cin.ignore(1024, '\n');
			switch (choice11){
			case '1':
				craft_gold_collection_use_all_dust();
				break;
			case '2':
				craft_gold_collection();
				break;
			default:
				break;
			}
			cout << endl << gold_commons_crafted << " Golden Commons crafted." << endl;
			cout << endl << gold_rares_crafted << " Golden Rares crafted." << endl;
			cout << endl << gold_epics_crafted << " Golden Epics crafted." << endl;
			cout << endl << gold_legendaries_crafted << " Golden Legendaries crafted." << endl;
			calculate_progress();
			check_completion();
			if (reg_collection_finished == true && reg_notification == false){
				cout << endl;
				system("Pause");
				system("cls");
				cout << "Congratulations! You just completed the regular collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				reg_notification = true;
			}
			if (gold_collection_finished == true && gold_notification == false){
				cout << endl;
				system("Pause");
				system("cls");
				cout << "Congratulations! You just completed the GOLDEN collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Totally Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				gold_notification = true;
			}
			break;
		default:
			break;
		}
		break;
	case '6':
		calculate_progress();
		show_progress();
		break;
	case '7':
		system("Cls");
		cout << endl << "1. Complete regular collection (Disenchants extra cards and all golden cards)" << endl;
		cout << "2. Complete both regular and golden collection (Only disenchants extra cards)" << endl << endl;
		cout << "Choose an option (1, 2): ";
		char choice8;
		cin >> choice8;
		cin.ignore(1024, '\n');
		switch (choice8){
		case '1':
			if (reg_collection_finished == true){
				cout << endl << "The collection is already finished" << endl;
			}
			else{
				finish_collection_no_gold();
				system("Cls");
				cout << endl << "Packs opened to finish the regular collection: " << reg_collection_finished_packs << endl;
			}
			break;
		case '2':
			if (reg_collection_finished == true && gold_collection_finished == true){
				cout << endl << "Both collections are already finished" << endl;
			}
			else{
				finish_collection();
				system("Cls");
				cout << endl << "Packs opened to finish the regular collection: " << reg_collection_finished_packs << endl;
				cout << endl << "Packs opened to finish the golden collection: " << gold_collection_finished_packs << endl;
			}
			break;
		default:
			break;
		}
		break;
	case '8':
		system("Cls");
		cout << endl << "1. Complete regular collections (Disenchants extra cards and all golden cards)" << endl;
		cout << "2. Complete both regular and golden collections (Only disenchants extra cards)" << endl << endl;
		cout << "Choose an option (1, 2): ";
		char choice9;
		cin >> choice9;
		cin.ignore(1024, '\n');
		switch (choice9){
		case '1':
			finish_multiple_collection_no_gold();
			system("Cls");
			cout << endl << "On average " << avg_reg_pack << " packs are needed to complete a regular collection" << endl;
			cout <<  "Min packs required: " << min_reg_pack << endl;
			cout <<  "Max packs required: " << max_reg_pack << endl;
			break;
		case '2':
			finish_multiple_collection();
			system("Cls");
			cout << endl << "On average " << avg_reg_pack << " packs are needed to complete a regular collection" << endl;
			cout << endl << "On average " << avg_gold_pack << " packs are needed to complete a golden collection" << endl;
			break;
		default:
			break;
		}
		break;
	case '9':
		cout << endl << "Are you sure that you want to exit the program? (Y/N):";
		cin >> choice;
		cin.ignore(1024, '\n');
		if (choice == 'Y' || choice == 'y')
			terminate = true;
		break;
	default:
		print_menu();
		cout << endl << endl;
		cout << "Error: You have made an invalid choice. Please try again." << endl << endl;
		cout << "Enter your option (0 - 9): ";

		cin >> choice;
		terminate = operate(choice);
		break;
	}
	return terminate;
}

void create_collection(){
	system("cls");

	char choice1;

	cout << endl;
	cout << "Please enter your own collection or select one of the templates." << endl << endl;
	cout << "1. Goblins and Gnomes V1 ------- C: 47 - R: 40 - E: 19 - L: 17" << endl;
	cout << "2. Goblins and Gnomes V2 ------- C: 40 - R: 37 - E: 26 - L: 20" << endl;
	cout << "3. Expert Set ------------------ C: 94 - R: 81 - E: 37 - L: 33" << endl;
	cout << "4. The Grand Tournament -------- C: 50 - R: 40 - E: 22 - L: 20" << endl;
	cout << "5. The Grand Tournament DE 2/3 - C: 50 - R: 40 - E: 22 - L: 20" << endl;
	cout << "6. Enter your own collection" << endl << endl;
	cout << "Enter your choice (1, 2, 3, 4, 5, 6): ";

	cin >> choice1;
	cin.ignore(1024, '\n');

	de_one_third = false;

	if (choice1 == '1'){
		common_card_no = 47;
		rare_card_no = 40;
		epic_card_no = 19;
		legendary_card_no = 17;

		common_collection.clear();
		common_collection.resize(common_card_no);
		rare_collection.clear();
		rare_collection.resize(rare_card_no);
		epic_collection.clear();
		epic_collection.resize(epic_card_no);
		legendary_collection.clear();
		legendary_collection.resize(legendary_card_no);

		gold_common_collection.clear();
		gold_common_collection.resize(common_card_no);
		gold_rare_collection.clear();
		gold_rare_collection.resize(rare_card_no);
		gold_epic_collection.clear();
		gold_epic_collection.resize(epic_card_no);
		gold_legendary_collection.clear();
		gold_legendary_collection.resize(legendary_card_no);

		cout << endl << "Goblins and Gnomes V1 is selected." << endl;
	}
	if (choice1 == '2'){
		common_card_no = 40;
		rare_card_no = 37;
		epic_card_no = 26;
		legendary_card_no = 20;

		common_collection.clear();
		common_collection.resize(common_card_no);
		rare_collection.clear();
		rare_collection.resize(rare_card_no);
		epic_collection.clear();
		epic_collection.resize(epic_card_no);
		legendary_collection.clear();
		legendary_collection.resize(legendary_card_no);

		gold_common_collection.clear();
		gold_common_collection.resize(common_card_no);
		gold_rare_collection.clear();
		gold_rare_collection.resize(rare_card_no);
		gold_epic_collection.clear();
		gold_epic_collection.resize(epic_card_no);
		gold_legendary_collection.clear();
		gold_legendary_collection.resize(legendary_card_no);

		cout << endl << "Goblins and Gnomes V2 is selected." << endl;
	}
	if (choice1 == '3'){
		common_card_no = 94;
		rare_card_no = 81;
		epic_card_no = 37;
		legendary_card_no = 33;

		common_collection.clear();
		common_collection.resize(common_card_no);
		rare_collection.clear();
		rare_collection.resize(rare_card_no);
		epic_collection.clear();
		epic_collection.resize(epic_card_no);
		legendary_collection.clear();
		legendary_collection.resize(legendary_card_no);

		gold_common_collection.clear();
		gold_common_collection.resize(common_card_no);
		gold_rare_collection.clear();
		gold_rare_collection.resize(rare_card_no);
		gold_epic_collection.clear();
		gold_epic_collection.resize(epic_card_no);
		gold_legendary_collection.clear();
		gold_legendary_collection.resize(legendary_card_no);

		cout << endl << "Expert Set is selected." << endl;
	}
	if (choice1 == '4'){
		common_card_no = 50;
		rare_card_no = 40;
		epic_card_no = 22;
		legendary_card_no = 20;

		common_collection.clear();
		common_collection.resize(common_card_no);
		rare_collection.clear();
		rare_collection.resize(rare_card_no);
		epic_collection.clear();
		epic_collection.resize(epic_card_no);
		legendary_collection.clear();
		legendary_collection.resize(legendary_card_no);

		gold_common_collection.clear();
		gold_common_collection.resize(common_card_no);
		gold_rare_collection.clear();
		gold_rare_collection.resize(rare_card_no);
		gold_epic_collection.clear();
		gold_epic_collection.resize(epic_card_no);
		gold_legendary_collection.clear();
		gold_legendary_collection.resize(legendary_card_no);

		cout << endl << "Grand Tournament Set is selected." << endl;
	}
	if (choice1 == '5'){
		common_card_no = 50;
		rare_card_no = 40;
		epic_card_no = 22;
		legendary_card_no = 20;
		de_one_third = true;

		common_collection.clear();
		common_collection.resize(common_card_no);
		rare_collection.clear();
		rare_collection.resize(rare_card_no);
		epic_collection.clear();
		epic_collection.resize(epic_card_no);
		legendary_collection.clear();
		legendary_collection.resize(legendary_card_no);

		gold_common_collection.clear();
		gold_common_collection.resize(common_card_no);
		gold_rare_collection.clear();
		gold_rare_collection.resize(rare_card_no);
		gold_epic_collection.clear();
		gold_epic_collection.resize(epic_card_no);
		gold_legendary_collection.clear();
		gold_legendary_collection.resize(legendary_card_no);

		cout << endl << "Grand Tournament Set is selected." << endl;
	}
	if (choice1 == '6'){
		cout << endl ;
		cout << "Please only enter numbers." << endl << endl;
		cout << "Enter common cards in the set: ";
		cin >> common_card_no;
		cout << "Enter rare cards in the set: ";
		cin >> rare_card_no;
		cout << "Enter epic cards in the set: ";
		cin >> epic_card_no;
		cout << "Enter legendary cards in the set: ";
		cin >> legendary_card_no;

		common_collection.clear();
		common_collection.resize(common_card_no);
		rare_collection.clear();
		rare_collection.resize(rare_card_no);
		epic_collection.clear();
		epic_collection.resize(epic_card_no);
		legendary_collection.clear();
		legendary_collection.resize(legendary_card_no);

		gold_common_collection.clear();
		gold_common_collection.resize(common_card_no);
		gold_rare_collection.clear();
		gold_rare_collection.resize(rare_card_no);
		gold_epic_collection.clear();
		gold_epic_collection.resize(epic_card_no);
		gold_legendary_collection.clear();
		gold_legendary_collection.resize(legendary_card_no);

		cout << endl << "C: " << common_card_no << " - R: " << rare_card_no << " - E: " << epic_card_no << " - L: " << legendary_card_no << endl;
	}
	if (choice1 != '1' && choice1 != '2' && choice1 != '3' && choice1 != '4' && choice1 != '5' && choice1 != '6'){
		common_card_no = 94;
		rare_card_no = 81;
		epic_card_no = 37;
		legendary_card_no = 33;

		common_collection.clear();
		common_collection.resize(common_card_no);
		rare_collection.clear();
		rare_collection.resize(rare_card_no);
		epic_collection.clear();
		epic_collection.resize(epic_card_no);
		legendary_collection.clear();
		legendary_collection.resize(legendary_card_no);

		gold_common_collection.clear();
		gold_common_collection.resize(common_card_no);
		gold_rare_collection.clear();
		gold_rare_collection.resize(rare_card_no);
		gold_epic_collection.clear();
		gold_epic_collection.resize(epic_card_no);
		gold_legendary_collection.clear();
		gold_legendary_collection.resize(legendary_card_no);

		cout << endl << "You have made an invalid choice. Expert Set is selected." << endl;
	}

	fill(common_collection.begin(), common_collection.end(), 0);
	fill(rare_collection.begin(), rare_collection.end(), 0);
	fill(epic_collection.begin(), epic_collection.end(), 0);
	fill(legendary_collection.begin(), legendary_collection.end(), 0);

	fill(gold_common_collection.begin(), gold_common_collection.end(), 0);
	fill(gold_rare_collection.begin(), gold_rare_collection.end(), 0);
	fill(gold_epic_collection.begin(), gold_epic_collection.end(), 0);
	fill(gold_legendary_collection.begin(), gold_legendary_collection.end(), 0);

}

void convert_percentage(){
	common_chance, rare_chance, epic_chance, legendary_chance, gold_common_chance, gold_rare_chance, gold_epic_chance, gold_legendary_chance = 0;

	common_chance = common_percentage * 1000;
	rare_chance = rare_percentage * 1000;
	epic_chance = epic_percentage * 1000;
	legendary_chance = legendary_percentage * 1000;

	gold_common_chance = gold_common_percentage * 1000;
	gold_rare_chance = gold_rare_percentage * 1000;
	gold_epic_chance = gold_epic_percentage * 1000;
	gold_legendary_chance = gold_legendary_percentage * 1000;
}

void open_de_pack(){

	int cardtype, card;
	int seed;
	seed = rand() % 32000;
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::duration<double> sec;
	Clock::time_point t0 = Clock::now();
	typedef std::minstd_rand G;
	G g(seed);
	typedef std::uniform_int_distribution<> D;

	for (int i = 0; i < 5; i++){

		if (inpack_common == 4){
			D d(common_chance+1, 100000);
			cardtype = d(g); //common_chance+1 to 100000
		}
		else{
			D d(1, 100000);
			cardtype = d(g);
		}
		if (cardtype <= common_chance){
			dust+=5;
		}
		else if (cardtype <= common_chance + rare_chance){
			dust+=20;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance){
			dust+=100;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance){
			dust+=400;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance){
			dust+=50;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance + gold_rare_chance){
			dust+=100;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance + gold_rare_chance + gold_epic_chance){
			dust+=400;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance + gold_rare_chance + gold_epic_chance + gold_legendary_chance){
			dust+=1600;
		}
	}
	packs_opened++;
}

void open_pack(){
	inpack_common = 0;
	inpack_rare = 0;
	inpack_epic = 0;
	inpack_legendary = 0;
	inpack_gold_common = 0;
	inpack_gold_rare = 0;
	inpack_gold_epic = 0;
	inpack_gold_legendary = 0;

	int cardtype, card;
	int seed;
	seed = rand() % 32000;
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::duration<double> sec;
	Clock::time_point t0 = Clock::now();
	typedef std::minstd_rand G;
	G g(seed);
	typedef std::uniform_int_distribution<> D;

	D d(0,2);
	if (de_one_third && d(g) == 0) {
		open_de_pack();
		return;
	}

	for (int i = 0; i < 5; i++){

		if (inpack_common == 4){
			D d(common_chance+1, 100000);
			cardtype = d(g); //common_chance+1 to 100000
		}
		else{
			D d(1, 100000);
			cardtype = d(g);
		}
		if (cardtype <= common_chance){
			D d(0, common_card_no - 1);
			card = d(g); //0 to common_card_no-1
			common_collection[card] = common_collection[card] + 1;
			total_common++;
			inpack_common++;
		}
		else if (cardtype <= common_chance + rare_chance){
			D d(0, rare_card_no - 1);
			card = d(g); //0 to rare_card_no-1
			rare_collection[card] = rare_collection[card] + 1;
			total_rare++;
			inpack_rare++;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance){
			D d(0, epic_card_no - 1);
			card = d(g); //0 to epic_card_no-1
			epic_collection[card] = epic_collection[card] + 1;
			total_epic++;
			inpack_epic++;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance){
			D d(0, legendary_card_no - 1);
			card = d(g); //0 to legendary_card_no-1
			legendary_collection[card] = legendary_collection[card] + 1;
			total_legendary++;
			inpack_legendary++;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance){
			D d(0, common_card_no - 1);
			card = d(g); //0 to common_card_no-1
			gold_common_collection[card] = gold_common_collection[card] + 1;
			total_gold_common++;
			inpack_gold_common++;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance + gold_rare_chance){
			D d(0, rare_card_no - 1);
			card = d(g); //0 to rare_card_no-1
			gold_rare_collection[card] = gold_rare_collection[card] + 1;
			total_gold_rare++;
			inpack_gold_rare++;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance + gold_rare_chance + gold_epic_chance){
			D d(0, epic_card_no - 1);
			card = d(g); //0 to epic_card_no-1
			gold_epic_collection[card] = gold_epic_collection[card] + 1;
			total_gold_epic++;
			inpack_gold_epic++;
		}
		else if (cardtype <= common_chance + rare_chance + epic_chance + legendary_chance + gold_common_chance + gold_rare_chance + gold_epic_chance + gold_legendary_chance){
			D d(0, legendary_card_no - 1);
			card = d(g); //0 to legendary_card_no-1
			gold_legendary_collection[card] = gold_legendary_collection[card] + 1;
			total_gold_legendary++;
			inpack_gold_legendary++;
		}
	}
	packs_opened++;
}

void open_x_packs(int x){
	bool open_all = false;
	char choice4;
	int temp_common = 0;
	int	temp_rare = 0;
	int temp_epic = 0;
	int temp_legendary = 0;
	int temp_gold_common = 0;
	int temp_gold_rare = 0;
	int temp_gold_epic = 0;
	int temp_gold_legendary = 0;

	if (x > 5){
		cout << endl << "It seems like you are trying to open quite a few packs." << endl;
		cout << endl << "Would like to open them all at once? (Y/N): ";
		cin >> choice4;
		if (choice4 == 'Y' || choice4 == 'y'){
			open_all = true;
		}
	}
	if (open_all == false){
		system("cls");
		for (int i = 1; i <= x; i++){
			open_pack();
			temp_common = temp_common + inpack_common;
			temp_rare = temp_rare + inpack_rare;
			temp_epic = temp_epic + inpack_epic;
			temp_legendary = temp_legendary + inpack_legendary;

			temp_gold_common = temp_gold_common + inpack_gold_common;
			temp_gold_rare = temp_gold_rare + inpack_gold_rare;
			temp_gold_epic = temp_gold_epic + inpack_gold_epic;
			temp_gold_legendary = temp_gold_legendary + inpack_gold_legendary;

			calculate_progress();
			check_completion();

			if (reg_collection_finished == true && reg_notification == false){
				system("cls");
				cout << endl << "Congratulations! You just completed the regular collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				reg_notification = true;
				system("Pause");
				system("cls");
			}
			if (gold_collection_finished == true && gold_notification == false){
				system("cls");
				cout << endl << "Congratulations! You just completed the GOLDEN collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Totally Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				gold_notification = true;
				system("Pause");
				system("cls");
			}

			cout << "Pack " << i << endl << endl << "C: " << inpack_common << " - R: " << inpack_rare << " - E: " << inpack_epic << " - L: " << inpack_legendary;
			cout << " - GC: " << inpack_gold_common << " - GR: " << inpack_gold_rare << " - GE: " << inpack_gold_epic << " - GL: " << inpack_gold_legendary << endl << endl;
		}
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << endl << x << " Packs Opened" << endl << endl << "C: " << temp_common << " - R: " << temp_rare << " - E: " << temp_epic << " - L: " << temp_legendary;
		cout << " - GC: " << temp_gold_common << " - GR: " << temp_gold_rare << " - GE: " << temp_gold_epic << " - GL: " << temp_gold_legendary << endl;

	}
	else{
		system("cls");
		cout << endl << "Please wait, this might take a while..." << endl;
		for (int i = 1; i <= x; i++){
			open_pack();
			temp_common = temp_common + inpack_common;
			temp_rare = temp_rare + inpack_rare;
			temp_epic = temp_epic + inpack_epic;
			temp_legendary = temp_legendary + inpack_legendary;

			temp_gold_common = temp_gold_common + inpack_gold_common;
			temp_gold_rare = temp_gold_rare + inpack_gold_rare;
			temp_gold_epic = temp_gold_epic + inpack_gold_epic;
			temp_gold_legendary = temp_gold_legendary + inpack_gold_legendary;

			calculate_progress();
			check_completion();

			if (reg_collection_finished == true && reg_notification == false){
				system("cls");
				cout << endl << "Congratulations! You just completed the regular collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				reg_notification = true;
				system("Pause");
				system("cls");
				cout << endl << "Please wait, this might take a while..." << endl;
			}
			if (gold_collection_finished == true && gold_notification == false){
				system("cls");
				cout << endl << "Congratulations! You just completed the GOLDEN collection." << endl;
				cout << endl << "It only took " << packs_opened << " packs. Totally Worth." << endl << endl;
				reg_collection_finished_packs = packs_opened;
				gold_notification = true;
				system("Pause");
				system("cls");
				cout << endl << "Please wait, this might take a while..." << endl;
			}
		}
		system("cls");
		cout << endl << x << " Packs Opened" << endl << endl << "C: " << temp_common << " - R: " << temp_rare << " - E: " << temp_epic << " - L: " << temp_legendary;
		cout << " - GC: " << temp_gold_common << " - GR: " << temp_gold_rare << " - GE: " << temp_gold_epic << " - GL: " << temp_gold_legendary << endl;
	}
}

void show_percentage(){
	cout << endl << "Here are the current percentages for card rarity distribution" << endl << endl;
	cout << " C: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << common_percentage << "%";
	cout << "  R: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << rare_percentage << "%";
	cout << "  E: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << epic_percentage << "%";
	cout << "  L: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << legendary_percentage << "%" << endl;
	cout << "GC: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_common_percentage << "%";
	cout << " GR: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_rare_percentage << "%";
	cout << " GE: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_epic_percentage << "%";
	cout << " GL: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_legendary_percentage << "%" << endl;

	cout << endl << "Would you like to enter new values? (Y/N): ";
	char choice5;
	cin >> choice5;
	if (choice5 == 'Y' || choice5 == 'y'){
		cout << endl << "If the values you enter doesn't add up to 100, they will be scaled." << endl << endl;
		cout << "Please only enter numbers. Decimals after 3 will be ignored. Use dot." << endl;
		cout << endl << "Enter the chance to find common cards: ";
		cin >> common_percentage;
		cout << "Enter the chance to find rare cards: ";
		cin >> rare_percentage;
		cout << "Enter the chance to find epic cards: ";
		cin >> epic_percentage;
		cout << "Enter the chance to find legendary cards: ";
		cin >> legendary_percentage;
		cout << "Enter the chance to find golden common cards: ";
		cin >> gold_common_percentage;
		cout << "Enter the chance to find golden rare cards: ";
		cin >> gold_rare_percentage;
		cout << "Enter the chance to find golden epic cards: ";
		cin >> gold_epic_percentage;
		cout << "Enter the chance to find golden legendary cards: ";
		cin >> gold_legendary_percentage;

		if (common_percentage + rare_percentage + epic_percentage + legendary_percentage + gold_common_percentage + gold_rare_percentage + gold_epic_percentage + gold_legendary_percentage != 100){
			float scale = 1;
			scale = (common_percentage + rare_percentage + epic_percentage + legendary_percentage + gold_common_percentage + gold_rare_percentage + gold_epic_percentage + gold_legendary_percentage) / 100;

			common_percentage = common_percentage / scale;
			rare_percentage = rare_percentage / scale;
			epic_percentage = epic_percentage / scale;
			legendary_percentage = legendary_percentage / scale;
			gold_common_percentage = gold_common_percentage / scale;
			gold_rare_percentage = gold_rare_percentage / scale;
			gold_epic_percentage = gold_epic_percentage / scale;
			gold_legendary_percentage = gold_legendary_percentage / scale;

			cout << endl << "Values did not add up to 100. They were scaled." << endl << endl;
			system("Pause");
		}
		else {
			cout << endl << "Values added up to 100." << endl << endl;
			system("Pause");
		}

		system("cls");
		cout << "Here are the updated percentages for card rarity distribution" << endl << endl;
		cout << " C: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << common_percentage << "%";
		cout << "  R: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << rare_percentage << "%";
		cout << "  E: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << epic_percentage << "%";
		cout << "  L: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << legendary_percentage << "%" << endl;
		cout << "GC: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_common_percentage << "%";
		cout << " GR: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_rare_percentage << "%";
		cout << " GE: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_epic_percentage << "%";
		cout << " GL: " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << gold_legendary_percentage << "%" << endl;
	}
}

void disenchant_extras(){
	int initial_dust = dust;
	dust_created = 0;
	for (int i = 0; i < legendary_card_no; i++){
		while (legendary_collection[i] > 1){
			legendary_collection[i]--;
			dust += 400;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		while (epic_collection[i] > 2){
			epic_collection[i]--;
			dust += 100;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		while (rare_collection[i] > 2){
			rare_collection[i]--;
			dust += 20;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		while (common_collection[i] > 2){
			common_collection[i]--;
			dust += 5;
		}
	}
	for (int i = 0; i < legendary_card_no; i++){
		while (gold_legendary_collection[i] > 1){
			gold_legendary_collection[i]--;
			dust += 1600;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		while (gold_epic_collection[i] > 2){
			gold_epic_collection[i]--;
			dust += 400;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		while (gold_rare_collection[i] > 2){
			gold_rare_collection[i]--;
			dust += 100;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		while (gold_common_collection[i] > 2){
			gold_common_collection[i]--;
			dust += 50;
		}
	}
	dust_created = dust - initial_dust;
}

void disenchant_gold_cards(){
	int initial_dust = dust;
	gold_dust_created = 0;
	for (int i = 0; i < legendary_card_no; i++){
		while (gold_legendary_collection[i] > 0){
			gold_legendary_collection[i]--;
			dust += 1600;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		while (gold_epic_collection[i] > 0){
			gold_epic_collection[i]--;
			dust += 400;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		while (gold_rare_collection[i] > 0){
			gold_rare_collection[i]--;
			dust += 100;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		while (gold_common_collection[i] > 0){
			gold_common_collection[i]--;
			dust += 50;
		}
	}
	gold_dust_created = dust - initial_dust;
}

void craft_regular_collection(){
	legendaries_crafted = 0;
	epics_crafted = 0;
	rares_crafted = 0;
	commons_crafted = 0;

	for (int i = 0; i < legendary_card_no; i++){
		while ((legendary_collection[i] < 1) && (dust > 1600)){
			legendary_collection[i] += 1;
			dust -= 1600;
			legendaries_crafted++;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		while ((epic_collection[i] < 2) && (dust > 400) && (comp_leg == legendary_card_no)){
			epic_collection[i] += 1;
			dust -= 400;
			epics_crafted++;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		while ((rare_collection[i] < 2) && (dust > 100) && (comp_epic == epic_card_no)){
			rare_collection[i] += 1;
			dust -= 100;
			rares_crafted++;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		while ((common_collection[i] < 2) && (dust > 40) && (comp_rare == rare_card_no)){
			common_collection[i] += 1;
			dust -= 40;
			commons_crafted++;
		}
	}
}

int calculate_dust_required_for_completion()
{
    int dust_required=0;
	for (int i = 0; i < legendary_card_no; i++){
		if (legendary_collection[i] < 1) {
			dust_required += 1600;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		dust_required += 400*(2-(epic_collection[i]>2?2:epic_collection[i]));
	}
	for (int i = 0; i < rare_card_no; i++){
		dust_required += 100*(2-(rare_collection[i]>2?2:rare_collection[i]));
	}
	for (int i = 0; i < common_card_no; i++){
		dust_required += 40*(2-(common_collection[i]>2?2:common_collection[i]));
	}
	return dust_required;
}

void craft_regular_collection_use_all_dust(){
	legendaries_crafted = 0;
	epics_crafted = 0;
	rares_crafted = 0;
	commons_crafted = 0;

	for (int i = 0; i < legendary_card_no; i++){
		while ((legendary_collection[i] < 1) && (dust > 1600)){
			legendary_collection[i] += 1;
			dust -= 1600;
			legendaries_crafted++;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		while ((epic_collection[i] < 2) && (dust > 400)){
			epic_collection[i] += 1;
			dust -= 400;
			epics_crafted++;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		while ((rare_collection[i] < 2) && (dust > 100)){
			rare_collection[i] += 1;
			dust -= 100;
			rares_crafted++;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		while ((common_collection[i] < 2) && (dust > 40)){
			common_collection[i] += 1;
			dust -= 40;
			commons_crafted++;
		}
	}
}

void craft_gold_collection(){
	gold_legendaries_crafted = 0;
	gold_epics_crafted = 0;
	gold_rares_crafted = 0;
	gold_commons_crafted = 0;

	for (int i = 0; i < legendary_card_no; i++){
		while ((gold_legendary_collection[i] < 1) && (dust > 3200) && (comp_com == common_card_no)){
			gold_legendary_collection[i] += 1;
			dust -= 3200;
			gold_legendaries_crafted++;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		while ((gold_epic_collection[i] < 2) && (dust > 1600) && (comp_gold_leg == legendary_card_no)){
			gold_epic_collection[i] += 1;
			dust -= 1600;
			gold_epics_crafted++;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		while ((gold_rare_collection[i] < 2) && (dust > 800) && (comp_gold_epic == epic_card_no)){
			gold_rare_collection[i] += 1;
			dust -= 800;
			gold_rares_crafted++;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		while ((gold_common_collection[i] < 2) && (dust > 400) && (comp_gold_rare == rare_card_no)){
			gold_common_collection[i] += 1;
			dust -= 400;
			gold_commons_crafted++;
		}
	}
}

void craft_gold_collection_use_all_dust(){
	gold_legendaries_crafted = 0;
	gold_epics_crafted = 0;
	gold_rares_crafted = 0;
	gold_commons_crafted = 0;

	for (int i = 0; i < legendary_card_no; i++){
		while ((gold_legendary_collection[i] < 1) && (dust > 3200)){
			gold_legendary_collection[i] += 1;
			dust -= 3200;
			gold_legendaries_crafted++;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		while ((gold_epic_collection[i] < 2) && (dust > 1600)){
			gold_epic_collection[i] += 1;
			dust -= 1600;
			gold_epics_crafted++;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		while ((gold_rare_collection[i] < 2) && (dust > 800)){
			gold_rare_collection[i] += 1;
			dust -= 800;
			gold_rares_crafted++;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		while ((gold_common_collection[i] < 2) && (dust > 400)){
			gold_common_collection[i] += 1;
			dust -= 400;
			gold_commons_crafted++;
		}
	}
}

void show_collection(){
	cout << "Here is the current collection" << endl;
	cout << endl << "C: " << common_card_no << " - R: " << rare_card_no << " - E: " << epic_card_no << " - L: " << legendary_card_no << endl;
}

void calculate_progress(){

	comp_leg = 0;
	comp_epic = 0;
	half_epic = 0;
	comp_rare = 0;
	half_rare = 0;
	comp_com = 0;
	half_com = 0;

	comp_gold_leg = 0;
	comp_gold_epic = 0;
	half_gold_epic = 0;
	comp_gold_rare = 0;
	half_gold_rare = 0;
	comp_gold_com = 0;
	half_gold_com = 0;

	for (int i = 0; i < legendary_card_no; i++){
		if (legendary_collection[i] >= 1){
			comp_leg++;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		if (epic_collection[i] == 1){
			half_epic++;
		}
		if (epic_collection[i] >= 2){
			comp_epic++;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		if (rare_collection[i] == 1){
			half_rare++;
		}
		if (rare_collection[i] >= 2){
			comp_rare++;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		if (common_collection[i] == 1){
			half_com++;
		}
		if (common_collection[i] >= 2){
			comp_com++;
		}
	}
	for (int i = 0; i < legendary_card_no; i++){
		if (gold_legendary_collection[i] >= 1){
			comp_gold_leg++;
		}
	}
	for (int i = 0; i < epic_card_no; i++){
		if (gold_epic_collection[i] == 1){
			half_gold_epic++;
		}
		if (gold_epic_collection[i] >= 2){
			comp_gold_epic++;
		}
	}
	for (int i = 0; i < rare_card_no; i++){
		if (gold_rare_collection[i] == 1){
			half_gold_rare++;
		}
		if (gold_rare_collection[i] >= 2){
			comp_gold_rare++;
		}
	}
	for (int i = 0; i < common_card_no; i++){
		if (gold_common_collection[i] == 1){
			half_gold_com++;
		}
		if (gold_common_collection[i] >= 2){
			comp_gold_com++;
		}
	}
}

void show_progress(){
	system("cls");

	cout << endl;
	cout << "                Half/ Comp/ Total" << endl << endl;
	cout << "   Legendaries:   - / " << setw(3) << comp_leg << " / " << setw(3) << legendary_card_no << endl;
	cout << "         Epics: " << setw(3) << half_epic << " / " << setw(3) << comp_epic << " / " << setw(3) << epic_card_no << endl;
	cout << "         Rares: " << setw(3) << half_rare << " / " << setw(3) << comp_rare << " / " << setw(3) << rare_card_no << endl;
	cout << "       Commons: " << setw(3) << half_com << " / " << setw(3) << comp_com << " / " << setw(3) << common_card_no << endl;
	cout << " Dust required: " << calculate_dust_required_for_completion() << endl;

	cout << "G. Legendaries:   - / " << setw(3) << comp_gold_leg << " / " << setw(3) << legendary_card_no << endl;
	cout << "      G. Epics: " << setw(3) << half_gold_epic << " / " << setw(3) << comp_gold_epic << " / " << setw(3) << epic_card_no << endl;
	cout << "      G. Rares: " << setw(3) << half_gold_rare << " / " << setw(3) << comp_gold_rare << " / " << setw(3) << rare_card_no << endl;
	cout << "    G. Commons: " << setw(3) << half_gold_com << " / " << setw(3) << comp_gold_com << " / " << setw(3) << common_card_no << endl;
}

void check_completion(){
	if (comp_leg == legendary_card_no && comp_epic == epic_card_no && comp_rare == rare_card_no && comp_com == common_card_no){
		reg_collection_finished = true;
	}
	if (comp_gold_leg == legendary_card_no && comp_gold_epic == epic_card_no && comp_gold_rare == rare_card_no && comp_gold_com == common_card_no){
		gold_collection_finished = true;
	}
}

void finish_collection(){
	calculate_progress();
	check_completion();
	while (reg_collection_finished == false){
		open_pack();
		disenchant_extras();
		if (calculate_dust_required_for_completion() < dust) {
			craft_regular_collection();
		}
		calculate_progress();
		check_completion();
	}
	reg_collection_finished_packs = packs_opened;

	while (gold_collection_finished == false){
		open_pack();
		disenchant_extras();
		craft_gold_collection();
		calculate_progress();
		check_completion();
	}
	gold_collection_finished_packs = packs_opened;
}

void finish_collection_no_gold(){
	calculate_progress();
	check_completion();
	while (reg_collection_finished == false){
		open_pack();
		disenchant_extras();
		disenchant_gold_cards();
		if (calculate_dust_required_for_completion() < dust) {
			craft_regular_collection_use_all_dust();
		}
		calculate_progress();
		check_completion();
	}
	reg_collection_finished_packs = packs_opened;
}

void finish_multiple_collection(){
	system("Cls");
	int this_reg_pack = 0;
	int this_gold_pack = 0;
	reg_collection_finished_packs = 0;
	gold_collection_finished_packs = 0;
	cout << endl << "This option might be time consuming depending on the collection size." << endl;
	cout << endl << "Experiment with small numbers first to find a suitable simulation number." << endl;
	cout << endl << "How many times would you like the collection to be completed?" << endl;
	cout << endl << "Please enter a number: ";
	int sim_no;
	cin >> sim_no;

	cout << endl << "Please wait, this might take a while..." << endl;
	finish_collection();

	this_reg_pack = reg_collection_finished_packs;
	avg_reg_pack = this_reg_pack;

	this_gold_pack = gold_collection_finished_packs;
	avg_gold_pack = this_gold_pack;
	reset_program();

	for (int i = 1; i < sim_no; i++){
		reg_collection_finished_packs = 0;
		gold_collection_finished_packs = 0;
		finish_collection();

		this_reg_pack = reg_collection_finished_packs;
		avg_reg_pack = ((avg_reg_pack * i) + this_reg_pack) / (i + 1);

		this_gold_pack = gold_collection_finished_packs;
		avg_gold_pack = ((avg_gold_pack * i) + this_gold_pack) / (i + 1);
		reset_program();
	}
}

void finish_multiple_collection_no_gold(){
	system("Cls");
	int this_reg_pack = 0;
	reg_collection_finished_packs = 0;

	cout << endl << "How many times would you like the collection to be completed?" << endl;
	cout << endl << "Please enter a number: ";
	int sim_no;
	cin >> sim_no;

	cout << endl << "Please wait, this might take a while..." << endl;
	finish_collection_no_gold();

	this_reg_pack = reg_collection_finished_packs;
	avg_reg_pack = this_reg_pack;
	min_reg_pack = this_reg_pack;
	max_reg_pack = this_reg_pack;

	reset_program();

	int total_packs=this_reg_pack;

	for (int i = 1; i < sim_no; i++){
		reg_collection_finished_packs = 0;
		finish_collection_no_gold();

		this_reg_pack = reg_collection_finished_packs;
		if (this_reg_pack > max_reg_pack) {
			max_reg_pack = this_reg_pack;
		}
		if (this_reg_pack < min_reg_pack) {
			min_reg_pack = this_reg_pack;
		}
		total_packs+=this_reg_pack;
		reset_program();
	}
	avg_reg_pack = total_packs/sim_no;
}

void reset_program(){
	total_common, total_rare, total_epic, total_legendary, total_gold_common, total_gold_rare, total_gold_epic, total_gold_legendary = 0;
	inpack_common, inpack_rare, inpack_epic, inpack_legendary, inpack_gold_common, inpack_gold_rare, inpack_gold_epic, inpack_gold_legendary = 0;
	packs_opened = 0;
	dust = 0;

	fill(common_collection.begin(), common_collection.end(), 0);
	fill(rare_collection.begin(), rare_collection.end(), 0);
	fill(epic_collection.begin(), epic_collection.end(), 0);
	fill(legendary_collection.begin(), legendary_collection.end(), 0);

	fill(gold_common_collection.begin(), gold_common_collection.end(), 0);
	fill(gold_rare_collection.begin(), gold_rare_collection.end(), 0);
	fill(gold_epic_collection.begin(), gold_epic_collection.end(), 0);
	fill(gold_legendary_collection.begin(), gold_legendary_collection.end(), 0);

	legendaries_crafted = 0;
	epics_crafted = 0;
	rares_crafted = 0;
	commons_crafted = 0;

	gold_legendaries_crafted = 0;
	gold_epics_crafted = 0;
	gold_rares_crafted = 0;
	gold_commons_crafted = 0;

	comp_leg = 0;
	comp_epic = 0;
	half_epic = 0;
	comp_rare = 0;
	half_rare = 0;
	comp_com = 0;
	half_com = 0;

	comp_gold_leg = 0;
	comp_gold_epic = 0;
	half_gold_epic = 0;
	comp_gold_rare = 0;
	half_gold_rare = 0;
	comp_gold_com = 0;
	half_gold_com = 0;

	reg_collection_finished = false;
	gold_collection_finished = false;

	reg_collection_finished_packs = 0;
	gold_collection_finished_packs = 0;

	reg_notification = false;
	gold_notification = false;
}
