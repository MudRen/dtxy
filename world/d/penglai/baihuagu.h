
inherit ROOM;
#include <room.h>
#include <ansi.h>

void create ()
{
  int north=(POS/10+4)%5*10+POS%10,south=(POS/10+1)%5*10+POS%10,
      east=POS/10*10+(POS%10+1)%5,west=POS/10*10+(POS%10+4)%5;
  set ("short", "�ٻ���");
  set ("long", @LONG

һƬƽ̹�ȵأ���������ɽ���ƣ�ɽ����������ƣ�
����һƬ���ɸ��ء������ļ���������ɫ�ʻ�������
���ޣ���Ŀ�����Ŀ������ӭ�ˣ���һƬ����Ǭ����
�������硣
LONG);

  set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"baihuagu"+north,
  "south" : __DIR__"baihuagu"+south,
  "east" : __DIR__"baihuagu"+east,
  "west" : __DIR__"baihuagu"+west,
]));
  set("outdoors",1);
  setup();
}
