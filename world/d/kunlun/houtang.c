inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ��ʯ�ң�����ֻ��һλ�ϵ���������ȫ��ʯ�ڣ�
    ֻ�е��������һ����ϸ������(rope)ͨ������һ�ߣ�
    ���������(climb) ��

LONG );
       set("exits", ([
               "south" : __DIR__"mishi",
       ]));

            set("objects",([
                __DIR__"npc/guang" : 1,
        ]));
        
       set("no_clean_up", 0);
       setup();
}
int valid_leave(object me,string dir)
{
        if(dir=="down" && (!me->query("family") || (me->query("family/family_name")!="����ɽ���鶴")) && present("niang",environment(me))) 
             return notify_fail("��������ֵ�ס�����ȥ·��˵������������ʦ���޵��ĵط������˲������ڣ�\n");
        return ::valid_leave(me,dir);
}
void init()
{
        add_action("do_climb", "climb");
}


int do_climb(string arg)
{       
        object me;
        me=this_player();

        if ( !arg || ((arg != "rope") ))
                return notify_fail("��Ҫ����ȥ��\n");
        else if(me->query("kee")<50)   
          {
           me->unconcious();
           message_vision("$N������ס�������������˹�ȥ��\n",me);
          }
        else
          {
           me->add("kee",-50); 
           message_vision("$N����һ����ֻ������һƬ��ã��\n",me);
           me->move("/d/kunlun/hundun");
           tell_room(environment(me),"ֻ��"+me->name()+"�����ҵ��Ǳ�����������\n", me);
           return 1;
           }
        return 1;
}
