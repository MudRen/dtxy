// Room: /d/jjf/sleep
inherit ROOM;

void create ()
{
  set ("short", "ģ����");
  set ("long", @LONG

ģģ�����У�������һ��İ���ĵط����������涼���Ʋʣ����㿴������
�ա����¶��������㿴�������档Ҳ��֪�������棬�ǻá�
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"sleep-2",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/pangu.c" : 1,
]));
  set("light_up", 1);
  set("valid_startroom", 1);

  setup();
}
