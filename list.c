#include "DS.h"

/* p-ийн зааж буй List-д x утгыг төгсгөлд хийнэ */
void l_push_back(List *p, Grid x)
{
  /* Энд оруулах үйлдлийг хийнэ үү */
  p->len++;
  struct Elm *temp = malloc(sizeof(struct Elm));
  temp->x = x;
  temp->next = NULL;
  if (p->head == NULL)
  {

    p->head = temp;
    p->tail = temp;
  }
  else
  {
    p->tail->next = temp;
    p->tail = temp;
  }
}

/* p-ийн зааж буй List-д x утгыг эхэнд хийнэ
   Бүх элементүүд нэг нэг байрлал хойшилно.
 */
void l_push_front(List *p, Grid x)
{
  /* Энд оруулах үйлдлийг хийнэ үү */
  p->len++;
  struct Elm *temp = malloc(sizeof(struct Elm));
  struct Elm *temp1 = malloc(sizeof(struct Elm));


  temp1 = p->head;
  temp->x = x;
  temp->next = NULL;
  if (p->head == NULL)
  {
    p->head = temp;
    p->tail = temp;
  }
  else
  {
    p->head = temp;
    p->head->next = temp1;
  }
}

/*
  p-ийн зааж буй List-д x утгыг pos байрлалд хийнэ
  pos болон түүнээс хойшхи элементүүд нэг байрлал ухарна.
  Тухайн байрлал List-ийн сүүлийн индексээс их бол төгсгөлд орно.
 */
/*
  p-ийн зааж буй List-н эхлэлээс гаргана.
  List-ийн бүх элементүүд нэг нэг байрлал урагшилна
 */
void l_pop_front(List *p)
{
  /* Энд гаргах үйлдлийг хийнэ үү */
  if (p->len == 1)
  {
    p->head = NULL;
    p->len--;
  }
  if (p->len > 1)
  {
    p->head = p->head->next;
    p->len--;
  }
}

/* p-ийн зааж буй List-н төгсгөлөөс гаргана */
void l_pop_back(List *p)
{

  /* Энд гаргах үйлдлийг хийнэ үү */
  if (p->len == 1)
  {
    p->head = NULL;
    p->len--;
  }
  else if (p->len > 1)
  {
    struct Elm *temp0 = malloc(sizeof(struct Elm));
    temp0 = p->head;

    while (p->head->next != p->tail)
    {
      p->head = p->head->next;
    }
    p->tail = p->head;
    p->head->next = NULL;

    p->head = temp0;

    p->len--;
  }
}

/* p-ийн зааж буй List-н pos байрлалаас гаргана.
   pos болон түүнээс хойшхи элементүүд нэг байрлал урагшилна.
   pos байрлалаас гарах боломжгүй бол юу ч хийхгүй.
 */

/*
  p-ийн зааж буй List-н утгуудыг хэвлэнэ.
  Хамгийн эхний элементээс эхлэн дарааллаар, нэг мөрөнд
  нэг л элемент хэвлэнэ.
 */
void l_print(List *p)
{
  /* Энд хэвлэх үйлдлийг хийнэ үү */
  if (p->len > 0)
  {
    struct Elm *temp = malloc(sizeof(struct Elm));
    temp = p->head;
    while (p->head != 0)
    {
      printf("%d\n", p->head->x);
      p->head = p->head->next;
    }
    p->head = temp;
  }
}


Elm *l_search(List *p, Grid x)
{
  struct Elm *temp0 = malloc(sizeof(struct Elm));
  temp0 = p->head;
  for (int i = 0; i < p->len; i++)
  {
    if (p->head->x.x == x.x && p->head->x.y == x.y)
    {
      Elm *temp1 = p->head;
      p->head = temp0;
      return temp1;
    }
    p->head = p->head->next;
  }
  p->head = temp0;
  return NULL;
}



/*
  p-ийн зааж буй List-с x тоог хайн олдсон хаягийг буцаана.
  Олдохгүй бол NULL хаяг буцаана.
 */

 Elm *l_search_noHead(List *p, Grid x)
{
  struct Elm *temp0;
  temp0 = p->head;
  p->head = p->head->next;
  for (int i = 0; i < p->len-1; i++)
  {
    if (p->head->x.x == x.x && p->head->x.y == x.y)
    {
      Elm *temp1 = p->head;
      p->head = temp0;
      return temp1;
    }
    p->head = p->head->next;
  }
  p->head = temp0;
  return NULL;
}

