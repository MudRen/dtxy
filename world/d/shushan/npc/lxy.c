// modified by vikee
//����ɽ���ɡ�dhxy-evil 2000.7.5
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int begin_go();
int ask_me();
int recruit_apprentice(object ob);
int attempt_apprentice(object me);
int do_report();

void create()
{
        set_name("����ң", ({ "li xiaoyao", "li", "xiaoyao" }));
        set("title","��ɽ�������ŵ���");
        set("long", 
"����ң��Ľ��ݣ�����Ũü���ۣ������Ѱ���\n");
        set("gender", "����");
        set("age", 18);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("per", 30);
        set("kee", 2800);
        set("max_kee", 2800);
        set("sen", 1600);
        set("max_sen", 1600);
        set("force", 4800);
        set("max_force", 2400);
        set("mana", 4800);
        set("max_mana", 2400);
        set("force_factor", 60);
        set("mana_factor", 60);

        set("combat_exp", 1800000);
        set("daoxing", 2500000);

        set_skill("force", 150);
        set_skill("dodge", 160);
        set_skill("spells", 180);
        set_skill("parry", 140);
        set_skill("sword", 180);
        set_skill("canxin-jian", 200);
        set_skill("zixia-shengong", 130);
set_skill("sevensteps",160);
//        set_skill("jingya-sword", 130);
        set_skill("literate", 80);
        set_skill("taoism",120);
        map_skill("spells", "taoism");
        map_skill("force", "zixia-shengong");
map_skill("dodge", "sevensteps");
        map_skill("parry", "canxin-jian");
        map_skill("sword", "canxin-jian");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "sword","xiangsi" :),
                (: exert_function, "powerup" :),
        }) );

        set("inquiry", ([
                "��̨����": (: begin_go :),
            	"�����" : "���ܰ���ȥ��������ҿɻᱨ����ģ�\n",
                "���ʿ" : "�þ�û��ʦ���ˣ�\n",
                "ȥ������"     : (: ask_me :),
                "�������"     : (: do_report :),
		        "done"    : (: do_report :),
        ]));
        setup();
        create_family("��ɽ��", 5, "���ŵ���");
        carry_object("/obj/cloth")->wear();
        carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}

int attempt_apprentice(object me)
{
me =this_player();
//  if (me->query("family/family_name") != "��ɽ����" || me->query("myj/shushan") != "done")
   if (me->query("family/family_name") != "��ɽ��" || me->query("nyj/shushan") != "done")
  {
   command("say ֻ����ɽ���ӣ�ȥ�Ȼ���������ҲŻ��յġ�");
   return 0;
  }
//  if( (string)me->query("family/family_name")!="��ɽ��" )
//	  return 0;
  command("pat "+me->query("id"));
  command("say ����������ɣ�");
  command("recruit " + me->query("id") );
  return 1;
}

void init()
{
  object ob;

  ::init();
  if( interactive(ob = this_player()) && !is_fighting() )
  {
    remove_call_out("greeting");
    call_out("greeting", 1, ob);
  }
        add_action("do_nod", "nod");

}
void greeting(object ob)
{
        if( !ob || !present(ob, environment(this_object())) ) return;
        say( "����ң˵������λ" + RANK_D->query_respect(ob) +
"���ܲ��ܰ��Ҿȳ�����������ؽ����������ˣ�\n");
}

int do_report()
{
        int i=random(500)+1;
        object who = this_player();
        object me = this_object();
        if(who->query("nyj/shushan") == "done"){
        command("shake "+who->query("id"));
        return 1;
        }
//        if (objectp(present("zhao linger", environment(me)))) 
//        {       
        if (who->query_temp("shushan/linger_daying") == 1){
        command("thank "+who->query("id"));
        command("u&me "+who->query("id"));
        command("chat "+who->name()+"�ɹ��������������ȳ��������������������û�����������������ļ�¼��\n");
//        who->set("myj/shushan","done")
        who->set("nyj/shushan","done");
        who->add("daoxing",3000+i);
        tell_object(who,"��Ӯ����"+chinese_number(3)+"��"+chinese_number(i/4)+"��"+chinese_number((i-(i/4)*4)*3)+"ʱ���ĵ��У�\n");
        who->set("title","�ɽ�����");
        who->save();
        return 1;
        }
//        }
        command("? "+who->query("id"));
        return 1;
}

int ask_me()
{
        object ob=this_player();
        if(ob->query("nyj/shushan") == "done")
        {
        command("say лл�㣡�������鷳������");
        return 1;
        }
        command("wa");
        command("say �ðɣ������������ɹ��ȳ�����Ļ���һ��Ҫ�����ң�");        
        return 1;
}

int begin_go()
{
	object me;
    me=this_player();
	
	if(me->query_temp("save_linger"))
	{
        	command("say " + RANK_D->query_respect(me) + "�����������");
		return 1;
	}
	command("say �ðɣ���Ȼ�������ʦ�������ģ�������Ը��㡣ֻ��������������������ܿ࣬��֪" + RANK_D->query_respect(me) + "�ܷ�ǰȥ����һ�������ȳ�������nod��");        
    	me->set_temp("save_choose",1);
   return 1;
}

int do_nod()
{       
        object me,pass,ob;
        me=this_player();
        ob=this_object(); 
        if(!me->query_temp("save_choose"))
			return 0;
		me->delete_temp("save_choose");
        me->set_temp("save_linger",1);
        command("say ��Ȼ" + RANK_D->query_respect(me) + "��Ӧ����,����ң����л���ˣ�");        
		pass=new("/d/shushan/obj/lixiaoyao-pass");
		pass->move(me);
        message_vision("\n\n"NOR,me);
		command("bow");
        message_vision("\n\n"NOR,me);
		command("say " + RANK_D->query_respect(me) + "��ȥ��Σ������,����" + RANK_D->query_respect(me) + "���书Ӧ��û������,ֻ����������������
    ǧ��Ҫ��������,�м��мǣ�����");        
        message_vision("\n����ң����һ������ͷ��,�����н���������ȥ��\n\n"NOR,me);
        me->set("fangcun/panlong_nowayshushan",1);
		destruct (ob);
		return 1;

}

