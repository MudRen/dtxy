inherit ROOM;

void create ()
{
  set ("short", "ʯ��");
  set ("long", @LONG
    һ��ʯ��С·���Ѷ��ϣ��Ĵ��紵�ݶ��������չȻ������Ĵ���
ɽ�ͣ�·�������Եÿ�һЩ�������ƽ̹��
LONG);

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 2 */
  "westup" : __DIR__"shijie2",
  "southdown" : __DIR__"gate",
]));

  setup();
}
