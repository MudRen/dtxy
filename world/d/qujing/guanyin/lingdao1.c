inherit ROOM;

void create ()
{
  set ("short", "���");
  set ("long", @LONG

����������ǧ�¾��㡣�����˲��������������㡣ɽ�ݷ���
Ұ�����������ͱڣ�޵����������ƽ�ڡ�����˫������ʯ��
ҰԳ�����Ǹ��÷�⡣
LONG);
 
 set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/guai" : 2,
        ]));
  set("exits", ([
        "southup" : __DIR__"lingdao2",
        "northdown"  : __DIR__"lin8",
      ]));

  set("outdoors", __DIR__);

  setup();
}


