// lestat 2001


#include <ansi.h>

inherit NPC;

void create()
{
	    set_name(YEL"����������"NOR,({"monkey"}));
		set("title", YEL"�޷��ޱ�"NOR);
//        set("gender","����");
//        set("age", 60);
        set("str", 40);
        set("cor", 30);
		set("con", 30);
		set("cps", 30);
		set("spi", 30);
		set("int", 30);
//        set_temp("apply/damage", 125);
//        set_temp("apply/armor", 500);
 	    set_skill("unarmed", 100);
 	    set_skill("puti-zhi", 100);
 	    set_skill("dodge", 100);
   set_skill("jindouyun", 100);
   set_skill("parry", 100);
   set_skill("stick", 100);
   set_skill("qianjun-bang", 100);
   set_skill("force", 100);   
   set_skill("wuxiangforce", 100);
   //set_skill("literate", 100);
   set_skill("spells", 100);
   set_skill("dao", 100);
   map_skill("spells", "dao");
   map_skill("force", "wuxiangforce");
   map_skill("unarmed", "puti-zhi");
   map_skill("stick", "qianjun-bang");
   map_skill("dodge", "jindouyun");
   map_skill("parry", "qianjun-bang");
   set("combat_exp", 1000000);
   set("daoxing", 1000000);
     create_family("����ɽ���Ƕ�", 2, "����");
   set("chat_chance_combat", 90);
   set("chat_msg_combat", 
   ({
(: perform_action,"stick", "pili" :),
(: perform_action,"stick", "wu" :),
   }) );
   setup();
   carry_object("/d/obj/cloth/shoupiqun")->wear();
   carry_object("/d/obj/weapon/stick/bintiegun")->wield();
}

void copy_status(object me,object ob)
{
	me->set("name",YEL+ob->query("name")+NOR);
	me->set("gender",ob->query("gender"));
	me->set("age",ob->query("age"));
    me->set("nickname",ob->query("nickname"));
	me->set_skill("dodge", (int)ob->query_skill("dodge", 1));
	me->set_skill("parry", (int)ob->query_skill("parry", 1));
	me->set_skill("unarmed", (int)ob->query_skill("unarmed", 1));
	me->set_skill("spells", (int)ob->query_skill("spells", 1));
	me->set_skill("force", (int)ob->query_skill("force", 1));
          me->set_skill("stick", (int)ob->query_skill("spells", 1));
          me->set_skill("jindouyun", (int)ob->query_skill("spells", 1));
          me->set_skill("puti-zhi", (int)ob->query_skill("spells", 1));
	me->set_skill("qianjun-bang", (int)ob->query_skill("spells", 1));
    me->set_skill("wuxiangforce", (int)ob->query_skill("spells", 1));
	me->set_skill("dao", (int)ob->query_skill("spells", 1));
   me->set("max_kee",ob->query("max_kee"));
   me->set("eff_kee",ob->query("eff_kee"));
   me->set("kee",ob->query("kee"));

   me->set("max_gin",ob->query("max_gin"));
   me->set("eff_gin",ob->query("eff_gin"));
   me->set("gin",ob->query("gin"));

   me->set("max_sen",ob->query("max_sen"));
   me->set("eff_sen",ob->query("eff_sen"));
   me->set("sen",ob->query("sen"));

   me->set("max_force",ob->query("max_force"));
   me->set("force",ob->query("force"));
   me->set("force_factor",ob->query("force_factor"));

   me->set("max_mana",ob->query("max_mana"));
   me->set("mana",ob->query("mana"));
   me->set("mana_factor",ob->query("mana_factor"));
   me->set("combat_exp",ob->query("combat_exp"));
   me->set("daoxing",ob->query("daoxing"));
}

void die()
{
        message("vision",
                name() + YEL+"֨֨����˼�����һ�����������ƶ˲����ˡ�\n" NOR,environment(),
                this_object() );
        destruct(this_object());
}

int heal_up()
{
   object me=this_object();
   object who=present(me->query("leader"),environment(me) );
        if( environment() && (!is_fighting() || !objectp(who) || !who->is_fighting() )  ) {
                call_out("die", 1);
                return 1;
        }
   if( (int)me->query("time") > 10 ) {
     call_out("die",1);
     return 1;
   }
   add("time", 1);
        return ::heal_up() + 1;
}

void invocation(object who)
{
   int i;
   object me,*enemy;

   me=this_object();
   message("vision",
     YEL +who->query("name")+"֨֨����˼��������ƶ�һ���������˳�����\n" NOR,
     environment(),this_object());
   copy_status(me,who);
   enemy=who->query_enemy();
   i=sizeof(enemy);
   while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        kill_ob(enemy[i]);
                        if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
                        else enemy[i]->kill_ob(this_object());
                }
        }
   set("leader", (string)who->query("id"));
        set_leader(who);
}




