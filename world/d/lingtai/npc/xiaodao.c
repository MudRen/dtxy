// worker.c
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("ɨ��Сͯ", ({"xiao tong"}));
        set("gender", "����" );
        set("age", 13);
        set("long", "һ��Сͯ�����������ɨ��");
        set("combat_exp", 1000);
	set_skill("stick", 20);
	set_skill("dodge", 40);
        set("attitude", "friendly");
        set("chat_chance_combat", 50 );
        setup();
	carry_object("/d/lingtai/obj/shaoba")->wield();
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
        
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;

				message_vision("\n"NOR,ob);
                command ("say ��.....��......");
   				message_vision("\n��������������צ,���볤��,��Сͯ������ɫ�԰�,˫�ȷ���!"NOR,ob);
				message_vision("\n�ŵ�һƨ�����ڵ���,�����������!\n"NOR,ob);

}
void destroy(object ob)
{
        destruct(ob);
        return;
}
