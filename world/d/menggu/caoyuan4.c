// Room: /d/menggu/caoyuan4
inherit ROOM;

void create()
{
  set ("short", "Į����ԭ");
  set ("long", @LONG
���ƴ��������տ��ٵ��ƶ�����,�������������ڲ�ס����,����
�¾��ǹ����Į����ԭ,Զ��������������һƬ�����Ӫ��,�Ǿ�����������
�Ĳ���.
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"caoyuan5",
  "south" : __DIR__"caoyuan",
]));
  set("outdoors", "menggu");
  setup();
  replace_program(ROOM);
}

