inherit ROOM;

void create ()
{
  set ("short", "С·");
  set ("long", @LONG
    �ۿ��Ѿ�����С·�ľ�ͷ�ˣ�����æ�ӿ���
������

LONG);

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"gate",
  "east" : __DIR__"xiaolu2",
]));

  setup();
}
