#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <time.h>
#include <functional>
#include <cstring>
using namespace std;

#define MAX_ROWS 3
#define MAX_COLS 10
#define MAX_STUDENTS 30

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define NOTHING 0
#define APPLEPIE 1
#define BEEF 2
#define CURRY 3


typedef int MEALTYPE;

class Fmart; // this line is used to identify Fmart as a type name, since class Player and class Student have pointers to Fmart.

// ------------------------------Helper functions--------------------------------------//
int randInt(int min, int max)
{
    if (max < min)
		swap(max, min);
    return rand() % (max - min + 1) + min;
}
// -----------------------------Class Declarations-------------------------------------//
class Player 
{
public:

    //constructor
    Player(Fmart* fp);
    
    //destructor
    ~Player();

    //accessors
    int row() const;            
    int col() const;            
    int lives() const;          
    int score() const;
    MEALTYPE mealInHand() const;

    //mutators
    void pickup(MEALTYPE meal);
    void move(int dir);
    void soreup();
    void deliver();
    void decLife();

private:
    int m_row;
    int m_col;
    int m_lives;
    int m_score;
    MEALTYPE m_mealInHand;
    Fmart* m_fp;
};

class Student{
public:
    //constructor
    Student(Fmart* fp, int row, int col);

    //destructor
    ~Student();

    //accessors
    int row() const;
    int col() const;
    MEALTYPE typeWanted() const;

    //mutators
    void moveForward();   

private:
    // TODO: add private members for Student class.
    int m_row;
    int m_col;
    MEALTYPE m_mealWants;
    Fmart* m_fp;
};

class Fmart{
public:
    //constructor
    Fmart();
    
    //destructor
    ~Fmart();

    //accessors
    Player* getPlayer() const;
    int numberOfStudents() const;
    bool studentAt(int row, int col) const;
    MEALTYPE getStudentmeal(int row, int col);

    //mutators
    bool addStudent();
    bool deleteStudent(int row, int col);
    void display();
    void play();
    //void decLife();
private:
    Player* m_player;
    Student** m_students;
    int m_numStudents;
};

//---------------------------Implementions of Fmart-------------------------------------//

Fmart::Fmart()  
{
    // This constructor:
    // (1) adds a new player
    // (2) initializes m_students to be NULL (or nullptr)
    // (3) initializes the number of students to be 0.
    // TODO: finish the implementation.
    m_students = new Student* [MAX_STUDENTS];
    //m_students = NULL;
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        m_students[i] = NULL;
    }
    m_player = new Player(this);
    m_numStudents = 0;
}
Fmart::~Fmart()
{ 
    // TODO: delete everything you dynamically created.
    delete m_player;
    for (int i = 0; i < m_numStudents; i++)
    {
        delete m_students[i];
    }
    delete [] m_students;
}

Player* Fmart::getPlayer() const
{
    // This function returns a pointer to the player.
    // TODO: finish the implementation.
    return m_player;
    //return nullptr; // This line is only for the program to compile.
}

int Fmart::numberOfStudents() const
{
    // This function returns the number of students.
    // TODO: finish the implementation.
    return m_numStudents;
    //return 0; // This line is only for the program to compile.
}

bool Fmart::studentAt(int row, int col) const
{
    // TODO: check if there is a student at (row, col), if so, return true, else return false.
    for (int i = 0; i < m_numStudents; i++)
    {
        if ((m_students[i]->row() == row)&&(m_students[i]->col() == col))
        {
            return true;
        }
        
    }
    return false; // This line is only for the program to compile.
}

bool Fmart::addStudent()
{
    // TODO: add a new student at the rightmost column. 
    // If Student number is greater than MAX_STUDENTS, just do nothing and return false.
    // If you added a student successfully, return true.
    // You will need randInt() to get a random number.
    if(m_numStudents < MAX_STUDENTS)
    {
        m_students[m_numStudents] = new Student(this, randInt(1, 3), 10);
        m_numStudents++;
        return true;
    }
    return false; // This line is only for the program to compile.
}

bool Fmart::deleteStudent(int row, int col)
{
    for (int i = 0; i < m_numStudents; i++)
    {
        if ((m_students[i]->row() == row)&&(m_students[i]->col() == col))
        {
            delete m_students[i];
            memcpy(m_students + i, m_students + i + 1, sizeof(Student*) * (MAX_STUDENTS - i - 1));
            m_numStudents--;
            delete m_students[m_numStudents];
            m_students[m_numStudents] = NULL;
            return true;
        }
    }
    // TODO: delete a student at position (row, col) from m_students.
    // If no student is at this position, return false.
    // If there is a student, delete the student, and shift all students after it to the left.
    // Maybe there are extra things to deal with?
    // YOUR CODE HERE
    return false; // This line is only for the program to compile.
}

/** Display the game grid
 * It will display grids, players and students.
 * There are a few blanks for you to fill in.
 */
void Fmart::display()
{
    char** disp = new char* [3];
    for (int i = 0; i < 3; i++)
    {
        disp[i] = new char[10];
        for (int j = 0; j < 10; j++)
            disp[i][j] ='.';
    }

    // TODO: Visit each student and:
    // (Assume this student is at (r, c))
    // If this student wants the meal the player is atholding, change disp[r-1][c-1] to '@'.
    // If this student doesn't want the meal, change disp[r-1][c-1] to 'S'.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(studentAt(i+1, j+1))
            {
                disp[i][j] = 'S';
                if(getStudentmeal(i+1, j+1) == m_player->mealInHand())
                {
                    disp[i][j] = '@';
                }
            }
        }
    }
    // TODO: Check the type of meal the player is holding.
    // (Assume the player is at (r, c))
    // If it is APPLEPIE, change disp[r-1][c-1] to 'A';
    // If it is BEEF, change disp[r-1][c-1] to 'B';
    // If it is CURRY, change disp[r-1][c-1] to 'C';
    // If it is NOTHING, change disp[r-1][c-1] to 'P';

    if(m_player->mealInHand() == NOTHING)
    {
        disp[(m_player->row())-1][(m_player->col())-1] = 'P';
    }
    if(m_player->mealInHand() == APPLEPIE)
    {
        disp[(m_player->row())-1][(m_player->col())-1] = 'A';
    }
    if(m_player->mealInHand() == BEEF)
    {
        disp[(m_player->row())-1][(m_player->col())-1] = 'B';
    }
    if(m_player->mealInHand() == CURRY)
    {
        disp[(m_player->row())-1][(m_player->col())-1] = 'C';
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++)
            cout << disp[i][j];
        cout << endl;
    }
    for (int i = 0; i < 3; i++)
        delete[] disp[i];
    delete[] disp;
}

void Fmart::play()
{
    addStudent(); //Adds the first student.
    while (m_player->lives() > 0)
    {
        display();
        cout << "You have " <<m_player->lives() <<" lives, and your score is " <<m_player->score()<<"."<<endl;
        cout << "make a move (a, b, c, u, d, g): " << endl;
        string input;
		getline(cin, input);
        cout << endl << endl << endl;
        char option = input[0]; //Here, option is 'a', 'b', 'c', 'u', 'd', or 'g'.

        if(option == 'a')
        {
            m_player->pickup(APPLEPIE);
        }
        if(option == 'b')
        {
            m_player->pickup(BEEF);
        }
        if(option == 'c')
        {
            m_player->pickup(CURRY);
        }
        if(option == 'u')
        {
            m_player->move(1);
        }
        if(option == 'd')
        {
            m_player->move(0);
        }
        if(option == 'g')
        {
            m_player->deliver();
        }
        // TODO: Let your player behave according to 'option'.
        // You should call member functions of class Player.
        // Moves all students forward
        for (int i = 0; i < m_numStudents; i++){
            int detector = m_numStudents; // Detect whether a student has reached col 1 and is deleted.
            m_students[i]->moveForward();
            if(m_numStudents != detector)
                i--;                      // If so, move back 1 iteration.
        }
        // A 30% chance for adding a new student
        if(randInt(1,10) <= 3)
            addStudent();
    }
    cout << "You lose. Your score is " << m_player->score() <<". Press any key to quit." << endl;
    getchar();
}
MEALTYPE Fmart::getStudentmeal(int row, int col)
{
    for (int i = 0; i < m_numStudents; i++)
    {
        if ((m_students[i]->row() == row)&&(m_students[i]->col() == col))
        {
            return m_students[i]->typeWanted();
        }
    }
    return NOTHING;
}
//---------------------------Implementions of Student -------------------------------------//
Student::Student(Fmart* fp, int row, int col)
{
    m_row = row;
    m_col = col;
    m_fp = fp;
    m_mealWants = randInt(1,3);
    // TODO: this constructor initializes a student, at (row, col).
    // You should randomly choose 1 meal type, and store it in the student object.
    // fp is a pointer to the Fmart this student is in.

}

Student::~Student()
{
    // TODO: delete everything you dynamically created.
}

int Student::row() const
{
    return m_row;// TODO: return the row number.
    //return 0; // This line is only for the program to compile.
}

int Student::col() const
{
    return m_col;// TODO: return the column number.
    //return 0; // This line is only for the program to compile.
}

MEALTYPE Student::typeWanted() const
{
    return m_mealWants;// TODO: return the type of meal this student wants.
    //return NOTHING; // This line is only for the program to compile.
}

void Student::moveForward()
{
    // TODO: 
    // Move the student forward for one step.
    // If this student reaches the first column, player's lives will be decreased by 1, and this student will be deleted.
    // YOUR CODE HERE
    m_col--;
    if (m_col == 1)
    {
        m_fp->deleteStudent(m_row, m_col);
        m_fp->getPlayer()->decLife();
    }
    //return; // This line is only for the program to compile.
}

//---------------------------Implementions of Player -------------------------------------//

Player::Player(Fmart* fp)
{
    // TODO: this constructor initializes the player.
    // For example, the player should be at (2, 1), have 3 lives, and have 0 score.
    // Please consider other parameters to initialize.
    m_row = 2;
    m_col = 1;
    m_lives = 3;
    m_score = 0;
    m_mealInHand = 0;
    m_fp = fp;
}

Player::~Player()
{
    
    // TODO: delete everything you dynamically created.
}

int Player::row() const
{
    return m_row;
    // TODO: return the row number.
    //return 0; // This line is only for the program to compile.
}     
int Player::col() const
{
    
    return m_col;
    // TODO: return the column number.
    //return 0; // This line is only for the program to compile.
}

int Player::lives() const
{
    return m_lives;
    // TODO: return the number of lives.
    //return 1; // This line is only for the program to compile.
}          

int Player::score() const
{
    return m_score;
    // TODO: return the score.
    //return 0; // This line is only for the program to compile.
}

MEALTYPE Player::mealInHand() const
{
    return m_mealInHand;
    // TODO: return the type of meal in player's hand.
    //return NOTHING; // This line is only for the program to compile.
}

void Player::pickup(MEALTYPE meal)
{

    m_mealInHand = meal;
    // TODO: pick up a box meal of type 'meal'.
    //return; // This line is only for the program to compile.
}

void Player::move(int dir) 
{
    if(m_row == 1)
    {
        if (dir == 0)
        {
            m_row++;
        }
    }
    else if(m_row == 2)
    {
        if(dir == 1)
        {
            m_row--;
        }
        else
        {
            m_row++;
        }
    }
    else
    {
        if(dir == 1)
        {
            m_row--;
        }
    }
    // TODO: Move the player upwards of downwards.
    // dir will be either UP or DOWN.
    //return; // This line is only for the program to compile.
}

void Player::deliver()
{
    for(int i = 0; i< 10; i++)
    {
        if((m_fp->studentAt(m_row, i+1) == true)&&(m_mealInHand == m_fp->getStudentmeal(m_row, i+1)))
        {
            m_score += 10;
            m_fp->deleteStudent(m_row, i+1);
            break;
        }
    }
    /*if ((m_mealInHand == m_fp->getStudentmeal())&&(m_row == m_fp->studentAtRow())&&(m_mealInHand != NOTHING))
    {
        
    }*/
    // TODO:
    // Send the meal to left-most student in that row.
    // If (1) He/She doesn't want this meal 
    //    (2) No student at this row
    //    (3) Player has no meal in hand
    // just do nothing and returns.
    // If success, delete the student, increment m_score by 10, and set player's hand to NOTHING
    //return; // This line is only for the program to compile.
}

void Player::decLife()
{
    m_lives--;
    // TODO: decrease player's life by 1.
    //return; // This line is only for the program to compile.
}

// ------------------------------Main function--------------------------------------//
int main()
{
    srand(time(NULL));
    Fmart f;
    f.play();
}