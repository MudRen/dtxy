//vikee
//1/8/2000

inherit ROOM;

void create ()
{
  set ("short", "����");
  set ("long", @LONG

���ฮ�������ﴰ�����������ķ���һ�Ŵ����������Χ����һЩ̫
ʦ���Լ�һЩ�輸��������ʹ�á����ߵ���ͨ���ฮ���ţ��ϱ�����
һ��ͨ������������׳���

LONG);

  set("exits", ([
        "east" : __DIR__"yuxiang",
        "north" : __DIR__"bingqi",
        "south" : __DIR__"kuijia",
      ]));
  set("objects", ([
        __DIR__"npc/xiaotong" :  1,
      ]));

  setup();
}


