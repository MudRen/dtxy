inherit ROOM;

void create ()
{
  set ("short", "ʯ��");
  set ("long", @LONG

    ʯ����ǰ����������ԼԼ�ѿɿ���ɽ����ϼ���������Ƿ���
ɽ������ʱ�Ӵ��������о��������

�

LONG);

  set("exits", ([
        "north"   : __DIR__"lingyunge",
        "eastdown"   : __DIR__"shijie1",
      ]));
         set("outdoors", "xx" );  

  setup();
}
