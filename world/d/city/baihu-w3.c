//changan city

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","�׻����");
        set ("long", @LONG

�������ǰ׻���ֵ����Σ�����С������Լ����һ����Ĳ��ã�����
��һ�������ӣ���дһ�����ԡ��֡���������һ��������������լ��
����Сͬ��������ˣ���в�����ʦѧ��������Ԭ�ϲ�����ǰ��
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "south" : __DIR__"beiyin1",
                "north" : __DIR__"caotang",
                "west" : __DIR__"ximen",
                "east" : __DIR__"baihu-w2",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/libai" : 1,
        ]));


        set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
        
}

void init()
{
        object me;
        me = this_player();
        if(interactive(me))
        me->set_temp("intime", time());

}

int valid_leave(object me, string dir)
{
        int in_time;
        
        if (dir == "north")
        {
        in_time = me->query_temp("intime");
        me->set_temp("wait_time", time()-in_time);      
        }
        return 1;
}
