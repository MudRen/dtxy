// worker.c
#include <ansi.h>

inherit NPC;
string try_me(object me);

void create()
{
        set_name("𫲻��", ({"bo bufen", "bo"}));
        set("gender", "����" );
        set("age", 33);
        set("long", "һ���ֺ����ĵ�ʿ����ɵ�ǺǵĲ�֪Цʲô��\n");
	set("class", "taoist");
        set("combat_exp", 5000);
	set("daoxing", 10000);

        set("attitude", "friendly");

        set("chat_chance_combat", 50 );
        set("inquiry", ([
"Цʲô": "ʦ���ս���һ�����л�λ������������\n",
"���л�λ": "��ʦ��˵���԰��˴���Զ�����������Կ���\n",
"����": (: try_me :),
]) );
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
                if( !me || !visible(me) || environment(me) != environment() ) return;

				message_vision("\n"NOR,me);
	            command ("ah" );
				command ("say " + "ʦ��,�ⲻ����ʦ�嵱�������İ���������" );
				message_vision(WHT"\n\n�����Ӵ�Ц�������ǣ����ǣ�\n\n"NOR,me);
            call_out("destroy", 60, ob);
		}
       set("chat_chance", 10);
        set("chat_msg", ({
            (: random_move :)
        }) );
}

string try_me(object me)
{	me = this_player();
        command ("say ����Ҳ�ã�����");

message_vision("𫲻��˫����$Nͷ��һ�������˾����$N�Ժ�֮�к�����˳�ȥ������\n",
me);
	me->move("/d/lingtai/hill");
	return "���ˣ�����ô�����ˣ�";
}

void destroy(object ob)
{
        destruct(ob);
        return;
}