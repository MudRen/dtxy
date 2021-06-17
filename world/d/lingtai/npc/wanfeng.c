// worker.c

inherit NPC;

void create()
{
        set_name("���", ({"wan feng"}));
        set("title", "С����");
        set("gender", "����" );
        set("age", 16);
        set("long", "һ���Ե����ֵ�С��ʿ�������ջ�\n");
        set("combat_exp", 2000);
        set("attitude", "friendly");
        setup();

}
void init()
{
       object me,ob;
    me=this_player();
	ob=this_object();
::init();
        if (me->query_temp("fangcun/qiansi_gongxi")==1) 
		{
                remove_call_out("greeting");
                call_out("greeting", 1, me);
                call_out("destroy", 60, ob);
        }
		add_action("do_yao", "yao");
}

int do_yao(string arg)
{
        object m,mm;
        message_vision("$N������ʵ������֣���������\n", this_player());

        if((int)this_player()->query("food") >=
(int)this_player()->max_food_capacity()*90/100 )
        return notify_fail("���Ц����û�ǣ��ȿ���ʱ�����ɣ�\n");

        if((present("bao zi", this_player())))
        return notify_fail("���Ц������Ҫ��������ģ������Ź���ģ�����\n");
	
	if ( present("bao zi", environment()) )
                return notify_fail("���Ц�����ǲ�����һ�����������˵��\n");

        m=new("/d/obj/food/baozi");
        mm=new("/d/obj/food/baozi");


        m->move(this_player());
        mm->move(this_player());

        message_vision("����$NЦ�������˰ɣ�����ԡ�\n", this_player());
return 1;
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;

				command ("say " + "ʦ��,�������㣮���������ģ�" );

}

void destroy(object ob)
{
        destruct(ob);
        return;
}
