// Room: /d/nanhai/zhulin
inherit ROOM;

void create ()
{
  set ("short", "������");
  set ("long", @LONG

���Ӻ�ɽ�������֡�Ҳ�ǹ������������������ڡ�����ϸ�裬
���΢���������ڴˣ�����֮���Ŷ�ʱ������ɢ����������һ
С������
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"zhuli"+sprintf("%d",random(2)),
  "northwest" : __DIR__"zhuli"+sprintf("%d",random(7)),
  "southeast" : __DIR__"zhuli"+sprintf("%d",random(7)),
  "southwest" : __DIR__"zhuli4",
]));
  setup();
  replace_program(ROOM);
}
