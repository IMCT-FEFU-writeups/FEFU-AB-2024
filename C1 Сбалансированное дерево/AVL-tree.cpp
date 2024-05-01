#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct node
{
    int data;
    node *left;
    node *right;
    int height;
};

// Подсчёт веса узла
int height(node *t)
{
    return (t == NULL ? -1 : t->height);
}

// Малое правое
node *singleRightRotate(node *&t)
{
    if (t->left != NULL)
    {
        node *u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }
    return t;
}

// Малое левое
node *singleLeftRotate(node *&t)
{
    if (t->right != NULL)
    {
        node *u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }
    return t;
}
// ПЛ
node *doubleLeftRotate(node *&t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

// ЛП
node *doubleRightRotate(node *&t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

node *findMin(node *t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

// Добавление элемента
node *insert(int x, node *t)
{
    // Найдено место для элемента
    if (t == NULL)
    {
        t = new node;
        t->data = x;
        t->height = 0;
        t->left = t->right = NULL;
    }
    // Поиск места для элемента
    // В левое поддерево(лист)
    else if (x < t->data)
    {
        t->left = insert(x, t->left);
        // Перебалансировка
        if (height(t->left) - height(t->right) == 2)
        {
            // Добавили в лево
            if (x < t->left->data)
                t = singleRightRotate(t);
            // Добавили в право
            else
                t = doubleRightRotate(t);
        }
    }
    // В правое поддерево(лист)
    else if (x > t->data)
    {
        t->right = insert(x, t->right);
        // Перебалансировка
        if (height(t->right) - height(t->left) == 2)
        {
            // В право
            if (x > t->right->data)
                t = singleLeftRotate(t);
            // В лево
            else
                t = doubleLeftRotate(t);
        }
    }
    // Меняем вес узла
    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}

// Удаление элемента
node *remove(int x, node *t)
{
    node *temp;

    // Элемент не найден
    if (t == NULL)
        return NULL;

    // Поиск элемента
    else if (x < t->data)
        t->left = remove(x, t->left);
    else if (x > t->data)
        t->right = remove(x, t->right);

    // Элемент найден
    // Элемент с давумя потомками
    else if (t->left && t->right)
    {
        temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->data, t->right);
    }
    // С одним или без потомков
    else
    {
        temp = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        delete temp;
    }
    if (t == NULL)
        return t;

    // Меняем вес узла
    t->height = max(height(t->left), height(t->right)) + 1;

    // Если узел не сбалансирован
    // Если левый удалён
    if (height(t->left) - height(t->right) == -2)
    {
        // Левое правое вращение
        if (height(t->right->right) - height(t->right->left) == 1)
            return singleLeftRotate(t);
        // ПЛ вращение
        else
            return doubleLeftRotate(t);
    }
    // Если правый удалён
    else if (height(t->right) - height(t->left) == 2)
    {
        // Левое малое вращение
        if (height(t->left->left) - height(t->left->right) == 1)
        {
            return singleRightRotate(t);
        }
        // ЛП вращение
        else
            return doubleRightRotate(t);
    }
    return t;
}

// Вывод дерева
void display(node *t)
{
    if (t == NULL)
        return;
    display(t->left);
    fout << t->data << " ";
    display(t->right);
}

int main()
{

    node *t = NULL;
    int el;
    while (fin)
    {
        fin >> el;
        if (el > 0)
            t = insert(el, t);
        else if (el < 0)
            t = remove(el * (-1), t);
        else if (el == 0)
        {
            display(t);
            return 0;
        }
    }
}
