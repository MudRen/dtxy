// Room: /d/menggu/caoyuan6
inherit ROOM;

void create()
{
  set ("short", "Į����ԭ");
  set ("long", @LONG
���ƴ��������տ��ٵ��ƶ�����,�������������ڲ�ס����,����
�¾��ǹ����Į����ԭ,Զ��������������һƬ�����Ӫ��,�Ǿ�����������
�Ĳ���.
LONG);

  set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"shulin1",
  "southwest" : __DIR__"caoyuan5",
]));
  set("outdoors", "menggu");
  setup();
  replace_program(ROOM);
}

