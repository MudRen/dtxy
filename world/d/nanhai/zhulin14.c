// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// Room: /d/nanhai/zhulin.c

inherit ROOM;

void create ()
{
  set ("short", "������");
  set ("long", @LONG

���Ӻ�ɽ�������֡�Ҳ�ǹ������������������ڡ�����ϸ�裬
���΢���������ڴˣ�����֮���Ŷ�ʱ������ɢ��
LONG);

  set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"zhulin16",
  "west" : __DIR__"zhulin12",
  "north" : __DIR__"zhulin"+sprintf("%d", random(25)),
  "east" : __DIR__"zhulin"+sprintf("%d", random(25)),
]));

  setup();
  replace_program(ROOM);
}
