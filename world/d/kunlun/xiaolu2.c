inherit ROOM;

void create ()
{
  set ("short", "С·");
  set ("long", @LONG
    С·һֱ������ȥ������������·�ľ�ͷ��
LONG);

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"xiaolu3",
  "east" : __DIR__"xiaolu1",
]));

  setup();
}
