inherit ROOM;

void create ()
{
  set ("short", "С·");
  set ("long", @LONG
    ������һƬï�ܵ����֣���ʱ�����������޵Ľ�����
ֻ������һ��С·��֪ͨ��δ���
LONG);

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"xiaolu2",
  "east" : __DIR__"yaxia",
]));

  setup();
}
