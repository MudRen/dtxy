//Cracked by Roath

inherit ROOM;
void create()
{
  set ("short", "[1;33m����̨[m");
  set ("long", @LONG

��ǰ�����Ǵ�ٹ����ǵ������ֵĵط�������ݳ�˥���ˣ�
����ط�������û�˿����ˣ���ʹ������Ҳ������������̨
���Ա��и�С����(paizi)���������дЩʲô���ݡ�
LONG);
set("no_fight",1);
set("no_magic",1);
        set("exits", ([
        "north":__DIR__"dingan-3",
]));
        set("objects", ([
                __DIR__"npc/waiter": 1,
                ]));
        set("item_desc", ([
                "paizi": @TEXT
������������������������������������������������������������������������
                      ���㣺���ÿ����������,���������͵Ŀ��Ի�ö��⽱��
������������������������������������������������������������������������
TEXT
        ]) );
  setup();
}
int valid_leave(object me, string dir)
{       if (dir == "north"&& me->query("fish") )
        me->delete("fish"); 
        return 1;
}
/*
void say()
{
        object me=this_player();
         write("����͵Ķ���˵������~~��Ҫ���ű��˵��㡣\n");
        return 0;
}
*/
