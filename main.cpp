#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
void pr(string s,bool el = true)
{
    cout << s << (el?"\n":"\t");
}
class Book
{
private:
    string m_title;
    string m_author;
    string m_ISBN;
    string m_genre;
public:
    bool m_availability = true;
    Book() {}
    void set_title()
    {
        pr("Enter the title : ",false);
        cin.ignore();
        getline(cin,m_title);
    }

    void set_author()
    {
        pr("Enter the author : ",false);
        cin.ignore();
        getline(cin,m_author);
    }
    void set_ISBN()
    {
        pr("Enter the ISBN : ",false);
        cin.ignore();
        getline(cin,m_ISBN);
    }
    void set_genre()
    {
        pr("Enter the genre : ",false);
        cin.ignore();
        getline(cin,m_genre);
    }
    string print ()
    {
        return ("The title : " + m_title
                + "|\t The author : " + m_author
                + "|\t the ISBN : " + m_ISBN
                + "|\t The genre : " + m_genre
                + "| \t The availability : " + (m_availability?" available":" unavailable"));

    }
    string getTitle()
    {
        return m_title;
    }
    string getAuthor()
    {
        return m_author;
    }
    string getISBN()
    {
        return m_ISBN;
    }
    string getGenre()
    {
        return m_genre;
    }
};

template <class T>
class Container
{
private:
    T *data;
    size_t m_size;
    size_t m_capacity;
    int countRemove;
    int countBorrow;
    int avalability;

public:
    Container(size_t capacity = 0) : m_capacity (capacity)
    {
        countBorrow=0;
        countRemove=0;
        avalability=0;
        data = new T [m_capacity];
        m_size = 0;
    }
    ~Container()
    {
        delete [] data;
    }
    void insertfront()
    {
        for (int i = m_size; i > 0; i--)
        {
            data[i] = data[i-1];
        }
        m_size++;
        data[0].set_title();
        data[0].set_author();
        data[0].set_ISBN();
        data[0].set_genre();
        avalability++;
    }
    void insertat(int n)
    {
        for (int i = 0; i < m_size; i++)
        {
            if((i+1) == n)
            {

                for (int j = m_size; j >= n; j--)
                {
                    data[j] = data[j-1];
                }
                data[n-1].set_title();
                data[n-1].set_author();
                data[n-1].set_ISBN();
                data[n-1].set_genre();
                m_size++;
                avalability++;
            }
            else
            {
                pr("sorry this index out of size !!");
            }
        }
    }
    void insertend()
    {
        data[m_size].set_title();
        data[m_size].set_author();
        data[m_size].set_ISBN();
        data[m_size].set_genre();
        m_size++;
        avalability++;
    }
    void Remove(string title)
    {
        for (int i = 0; i < m_size; i++)
        {
            try
            {
                if(data[i].getTitle () == title)
                {
                    for (int j = i; j < m_size; j++)
                    {
                        data[j] = data[j+1];
                    }
                    m_size--;
                    cout<<"\t\t\t\t\t\tDone!!!!!!!!!"<<endl;
                    cout<<"\t\t\t\t\t\t-------------"<<endl;
                }
                else
                {
                    throw(title);
                }
            }
            catch(string title)
            {
                cout<<"There is no book with that name!!"<<endl;
                cout<<"Enter the title again: ";
                cin >>title;
                Remove(title);
            }
        }
        countRemove++;
        avalability--;
    }

    void print ()
    {
        for (int i = 0; i < m_size; i++)
        {
            pr(data[i].print());
        }
    }
    void borrowing(string name)
    {
        for(int i=0; i<m_size; i++)
        {
            try
            {
                if(data[i].getTitle()==name)
                {
                    data[i].m_availability="unavailable";
                    countBorrow++;
                    avalability--;
                    pr("\t\t\t\t\t\tDone!!!!!!!!!") ;
                    pr("\t\t\t\t\t\t-------------");
                }
                else
                {
                    throw (name);
                }
            }
            catch(string name)
            {
                pr("There is no book with that name!!");
                pr("Enter the title again: ",false);
                cin >>name;
                borrowing(name);
            }
        }
    }
    int get_size()
    {
        return m_size;
    }

    void enlarge (size_t capacity)
    {
        try
        {
            if(capacity > m_capacity)
            {
                T* newdata = new T [capacity];
                for (int i = 0; i < m_size; i++)
                {
                    newdata[i] = data[i];
                }
                delete [] data;
                data = newdata;
                m_capacity = capacity;

            }
            else
            {
                throw (capacity);
            }
        }
        catch(size_t capacity)
        {
            pr("This size smaller than the size of array!!");
            pr("------------------------------------------");
            pr("Enter the new capacity again: ",false);
            cin >> capacity;
            enlarge(capacity);
        }


    }

    void search(string key)
    {
        for (int i=0; i<=m_size; i++)
        {
            try
            {
                if(data[i].getTitle()==key)
                    pr(data[i].print());

                else if(data[i].getAuthor()==key)
                    pr(data[i].print());

                else if(data[i].getISBN()==key)
                    pr(data[i].print());

                else if(data[i].getGenre()==key)
                    pr(data[i].print());
                else
                    throw(key);
            }
            catch(string key)
            {
                pr("There is no data about this name!!");
                pr("----------------------------------");
                pr("Enter the name that you want to search about him again: ");
                cin >> key;
                search(key);
            }
        }
    }

    void sorting()
    {
        for(int j = 0; j < (m_size-1); j++)
        {
            for(int i = 0; i < m_size-j-1; i++)
            {
                if(data[i].getTitle()[0] > data[i+1].getTitle()[0])
                {
                    swap(data[i], data[i+1]);
                }

            }
        }
    }

    void Statistic()
    {
        cout << "The number of removed books: " << countRemove << endl;
        cout << "The number of borrowed books: " << countBorrow << endl;
        cout << "The number of available books: " << (m_size-(countBorrow+countRemove)) << endl;
    }
};

int main()
{
    Container <Book> b1(6);

    pr("\t\t\t## library management system ##");
    pr("\t\t-------------------------------------------------");
    int c;
    do
    {

        pr("###################################################");
        pr("## 1.Add new book.");
        pr("## 2.Search about book.");
        pr("## 3.Borrowing book.");
        pr("## 4.Statistic of books.");
        pr("## 5.Print all.");
        pr("## 6.Delete book with title.");
        pr("## 7.Enlarging the library.");
        pr("## 8.sorting the library.");
        pr("## 0.Exit the program.");
        pr("Enter you selection : ",false);
        cin >> c;

        switch(c)
        {
        case 1:
            pr("---------------------------------");
            pr("Add in the front (press 1)");
            pr("Add in the end (press 2)");
            pr("Add in the at (press 3)");
            pr("Enter your selection : ",false);
            cin >> c;
            if(c == 1)
                b1.insertfront();
            else if (c == 2)
                b1.insertend();
            else if (c == 3)
            {
                int n;
                pr("Enter the index : ",false);
                cin >> n;
                b1.insertat(n);
            }
            break;
        case 2:
        {
            string key;
            pr("Enter the title of the book you want to search: ");
            cin >>key;
            b1.search(key);
        }
        break;
        case 3:
        {
            string title;
            pr("Enter the title of the book that you want to borrow it");
            cin >> title;
            b1.borrowing(title);
        }
        break;
        case 4:
        {
            b1.Statistic();
            break;
        }

        case 5:
        {
            b1.print();
        }
        break;
        case 6:
        {
            string title;
            pr("Enter the title : ");
            cin >> title;
            b1.Remove(title);
        }
        break;
        case 7:
            int capacity;
            pr("Enter the new capacity : ",false);
            cin >> capacity;
            b1.enlarge(capacity);
            break;
        case 8:
            b1.sorting();
            b1.print();
            break;
        case 0:
            break;
        default:
            pr("Invalid choice please try again.");
            Sleep(3000);
        }
    }
    while(c != 0);
    return 0;
}
