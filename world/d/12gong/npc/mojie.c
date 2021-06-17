inherit NPC;
#include "star.h"
 
void create()
{
        set_name("����", ({"shura", "mo jie"}));
        set("long", "�ųƶ��ŵ������ҳϵ�ʥ��ʿ��ʮ����֮ս�У�Ϊ������������
ӵ���ŵ��ȴ���İ�˹������ʥ���� �ػ���ɽ����.\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("attitude", "friendly");
        set("age",37);
        set("con",45);
        set("per",30);
        set("str",63);
        set("int",64);
        set("combat_exp",10000000);
        set("daoxing",10000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "����˵������֪��ʱ���ټ����ŵ��ȣ�\n"   
        }));
        set_skill("dodge", 400);
        set("attitude", "friendly");
        set_skill("force", 400);
        set_skill("parry", 400);
        set_skill("unarmed", 400);
        set_skill("sword", 400);
        set_skill("westsword",400);
        set_skill("boxing",400);
        set_skill("balei",400);
        set_skill("spells",400);
        set_skill("renma", 400);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","renma");
        map_skill("dodge","balei");
        set("max_force",6000);
        set("force", 12000);
        set("max_mana",4000);
        set("mana",8000);
        set("mana_factor",50);
        set("force_factor",250);
        set("max_kee", 3000);
        set("max_gin", 3000);
        set("max_sen", 3000);

        setup();
        carry_object(__DIR__"obj/mj_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}

void init()
{
        add_action("do_none","perform");
        add_action("do_none","cast");
        add_action("do_none","ji");
}
int do_none()
{
        object me = this_object();
        message_vision("$N��Цһ��������$N��ǰ������ˣʲô������\n",me);
        return 1;
} 
void check()
{
        object ob=this_object();
        object ghost;
        object me2=new("/d/12gong/npc/mojie2.c");
        object me=query_temp("my_killer");

        if( ! me ) return ;
   if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }                               

     switch(random(4))
     {        
        case 0:
        {
        message_vision(HIY"$N���ڵ��ϣ���ؾ��ҵ����ţ�\n",ob);

        if(random(2)==0)
                {
              message_vision(HIY"$N����Ķ������ᣬʧȥ��ƽ�⣡\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(HIW"$Nվ�ȽŸ�����$n���������š�\n"NOR,me,ob);
        }
        break;


        case 1:
        {

        message_vision(HIC"$N��������,С������֮����,����һ��[ʥ��]����ն��!\n",ob,me);

                if(random(2)==0)

                {
              message_vision(HIM"$Nһ����С�ģ���[ʥ��]���˸�Ѫ������\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIG"$N����Ծ��[ʥ��]��$N�����»�����\n"NOR,me);
        }
        break;

   //     case 2:
   //     {

  //      message_vision(HIW"$Nҡ��һ�䣬�ֳ�����һ���Լ�����\n",ob);
//        if( present("kelowooz two",environment()));
  //      return;
 //       me2->move(environment());
 //       me2->kill_ob(me);
  //      }
   //     break;
                    

  }
        if( random(8) == 5 )
        powerup();

        remove_call_out("check");
        call_out("check",2+random(3));
}
void die()
{

        object ob = query_temp("my_killer");

        if((ob&&ob->query("12gong/renma")=="done") && (ob&&ob->query("12gong/mojie")!="done"))
        {
        ob->start_busy(3);
        message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
        "�����˵�ʮ��ɽ�򹬣�������ƽ�ʮ����ǰ����\n"NOR,users());
        ob->set("12gong/mojie","done");
        ob->add("12gong/number",1);
     ob->add("daoxing", 10000);
        tell_object(ob,"��Ӯ����ʮ�����");

        }
       ::die();
}

void unconcious()
{
  die();
}
