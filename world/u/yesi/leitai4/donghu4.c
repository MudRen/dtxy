// create by snowcat jan 21 1998

inherit ROOM;

void create ()
{
  set ("short", "����·");
  set ("long", @LONG

������һ��С·���������������ƣ���ˮ�峺͸������������������
���񡣷紵��ʱ����ˮ��������ϸ֦΢��������ɽӰ��ӡ�����߰���
��������������

LONG);

  set("exits", ([
        "west" : __DIR__"donghu3",
        "north" : __DIR__"donghu1",
        "southeast" : __DIR__"donghu6",
      ]));

  set("outdoors", __DIR__);

  setup();
}


