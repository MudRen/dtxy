//changan city

inherit ROOM;

void create ()
{
        set ("short", "����");
        set ("long", @LONG

����һ��������¡�����ꡣ���ϰ����ڹ�̨����Ц�ݿɾϵؽӴ��ſ�
�ˡ��������һ��ææµµ�ع����š���������޷��ģ��㻹������
��������ϰ��һЩ�㹤����׬һЩǮ�������ǽ������һ���ƾɵ�
��ʾ(gaoshi)��
LONG);

        set("item_desc", (["gaoshi" : "��������ȱ���֣������Ӷһ���̹����ɻ

work	��ʼ������
", ]));

        set("exits", 
        ([ //sizeof() == 4
		"west" : __DIR__"beiyin4",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/feng" : 1,
        ]));

//        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
}


void init()
{
//        add_action("do_work", "work");
}

int do_work(string arg)
{
        object ob;
        object me;

        me = this_player();

   if (! me->query_temp("working_in_liangdian")) {
message_vision("$N�ӳ���ж��һ�����Ĵ��ף�������ǽ�ߣ��۵��������ۣ�\n",me);
        me->add("kee",-30);
        me->add("sen",-30);
        ob = new("/obj/money/silver");
        ob->move(me);
        message_vision("���ϰ�Ц���еض�$N˵����������������Ĺ�Ǯ��\n",me);
        me->set_temp("working_in_liangdian",1);
        call_out ("reset_work",1,me);
    } else
    {
        message_vision("���ϰ�Ͻ���$N����������Ъһ�����\n",me);
    }
        return 1;
}
void reset_work (object me)
{
        me->set_temp("working_in_liangdian",0);
}

