// kulou.c ����
// tomcat


#include <ansi.h>
inherit NPC;


void create()
{
  object me = this_object();
  int j;
  set_name("����", ({"ku lou", "yao", "kulou"}));
  set("long","�ղŻ���һ���ɿݵĺ��ǣ�����֪��ô��ͻȻ�������ˣ����������������ģ�\n");
  set("gender", "����");
  set("age", 100);
  set("attitude", "peaceful");
  
   j= 200+random(100); 
        
    me->set_skill("unarmed", j);
    me->set_skill("dodge", j);
    me->set_skill("parry", j);
    me->set_skill("force", j);
    me->set_skill("spells", j);
 
    me->set_skill("blade", j+random(15));
    me->set_skill("kugu-blade", j+random(15));
    me->set_skill("sword",j+random(15));
    me->set_skill("qixiu-jian",j+random(15));
    me->set_skill("lingfu-steps", j+random(15));
    me->set_skill("yaofa", j+random(15));
    me->set_skill("huntian-qigong", j+random(15));
    me->set_skill("yinfeng-zhua", j+random(15));
     
   me->map_skill("force", "huntian-qigong");
   me->map_skill("blade", "kugu-blade");
   me->map_skill("sword","qixiu-jian");
   me->map_skill("parry", "kugu-blade");
   me->map_skill("spells", "yaofa");
   me->map_skill("dodge", "kugu-blade");
   me->map_skill("unarmed", "yinfeng-zhua");
  
     set("str",30);
     set("int",30);
     set("con",30);
     set("per",30);
     set("cor",30);
     set("spi",30);
     set("cps",30);
     set("kar",30);

        set("max_kee",3000+random(1000));
        set("eff_kee",3000+random(1000));
        set("kee",3000+random(1000));

        set("max_gin",2000+random(1000));
        set("eff_gin",2000+random(1000));
        set("gin",2000+random(1000));

        set("max_sen",2000+random(1000));
        set("eff_sen",2000+random(1000));
        set("sen",2000+random(1000));

        set("max_force",3000+random(1000));
        set("force",6000+random(1000));
        set("force_factor",300);

        set("max_mana",3000+random(1000));
        set("mana",6000+random(1000));
        set("mana_factor",300);
        set("combat_exp",500000+random(1000000));
        set("daoxing",100000+random(300000));
       
        set("nk_gain", 100+random(50));
        set("nk_factor", 50);

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
        (: perform_action,"blade", "diyu" :),
        (: perform_action,"blade", "pozhan" :),
        (: perform_action,"blade", "sword" :),
        }) );
  
  set("chat_chance", 10);
  set("chat_msg", ({
	"���õ�������Ҳ��֪������˯�˶���ˡ�\n",
	"���õ�����������㿪���ˡ�\n",
	}) );
  
  setup();
  carry_object("/d/obj/weapon/blade/blade")->wield();
}

/************************************************************/

void init()
{
 
  object me;

  ::init();
  if( interactive(me = this_player()) && !is_fighting() 
	  && living(me) ) {
    call_out("greeting", 1, me);
  }

}

void greeting(object me)
{
  
  object ob = this_object(); 
  if( !me || environment(me) != environment() ) return;
      kill_ob(me);
      me->kill_ob(ob);
      return;
 
}

void die()
{
    string msg;
    int mykar, diff;
    object wan;
    object ob = this_object();
    object me = this_player();
    msg="����ɢ��һ�Ѱ׹ǣ����˿�ȥ��\n";
    if(environment())
	message("vision", msg, environment());
    mykar=me->query_kar(); 
    diff=60-mykar;
    if( random(mykar) > diff) 
    {
       wan=new("/d/obj/drug/guo");
      if(environment()) wan->move(environment());
       msg=HIW"��ͻȻ���ְ׹Ƕ�������е㶫����\n"NOR;
       message("vision", msg, environment());
    }  
      destruct(this_object());
}
