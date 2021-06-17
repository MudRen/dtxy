// by happ@YSZZ
 
inherit NPC;
#include "star.h"
 
void create()
{
        set_name("����", ({"milo", "tian xie"}));
        set("long", "��ʮ����֮ս�У���ܱ��ӣ��������ֱ�����ʵ������ʱ��������
�Ӷɹ��ѹء�ڤ��֮ս�У�����С���汻����˹��ס��������ͷ֮һ����������˹��ܡ� 
�ػ�����Ы��.\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
        set("combat_exp",10000000);
        set("daoxing",3000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "����˵������֪��ʱ���ټ����ŵ��ȣ�\n"   
        }));
        set_skill("dodge", 250);
        set("attitude", "friendly");
        set_skill("force", 250);
        set_skill("parry", 250);
        set_skill("unarmed", 250);
        set_skill("sword", 250);
        set_skill("westsword",250);
        set_skill("boxing",250);
        set_skill("balei",250);
        set_skill("spells",250);
        set_skill("tianxie", 250);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","tianxie");
        map_skill("dodge","balei");
        set("max_force", 2000);
        set("force", 4000);
        set("max_mana",200);
        set("mana",4000);
        set("mana_factor",50);
        set("force_factor", 50);
        set("max_kee", 1500);
        set("max_gin", 1500);
        set("max_sen", 1500);

        setup();
        carry_object(__DIR__"obj/tx_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}
 
void check()
{
        object ob=this_object();
        object ghost;
        object me=query_temp("my_killer");
        if( ! me ) return ;
if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }                      
     switch(random(6))
     {        
        case 0:
        {
        message_vision(YEL"$Nһ����Ц��Ы�춾����$n��ȥ����\n",ob,me);

        if(random(2)==0)
                {
              message_vision(YEL"$N����ʮ����,ȫ������һ������У�\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
else        message_vision(YEL"$N��ʹ����ıܿ���[Ы�춾��]�Ľ�����\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(HIC"$N����һ������һ����ɫ�Ķ�����$n��ȥ��\n",ob,me);

        if(random(2)==0)

                {
              message_vision(YEL"$N��ʱ��Ѭ����ͷ��\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(YEL"$N��ת��ͣ������һ�ᶾ����ʧ����Ӱ���١�\n"NOR,me);
        }
        break;

        case 2:
        {

        
    //    ghost=new("/obj/npc/ghost.c");
    //    ghost->move(environment());
    //    ghost->set("combat_exp",ob->query("combat_exp"));
    //    ghost->set("max_kee",ob->query("max_kee"));
    //    ghost->set("max_sen",ob->query("max_sen"));
    //    ghost->kill_ob(ob);
        if(random(2)==0)
			{
		message_vision(HIR"$N�����ƽ�С����,ʹ����Ы����ǿ��һ��[������ʿ]!\n",ob);
		message_vision(HIC"��Ы����ֱ��������࣡\n"NOR,me);
        me->add("eff_kee",-2*query("max_kee")/10);
        me->add("eff_sen",-2*query("max_sen")/10);
	        }	
		}
        break;

  }
        if( random(8) == 5 )
        powerup();

        remove_call_out("check");
        call_out("check",2+random(3));
}
void die()
{
       object ob = query_temp("my_killer");

        
        if (ob->query_temp("12gong/cike") == "done")
			
			 message("chat",HIY+"���ƽ�ʮ����������(Milo):"+ob->name()+
             "ǿ�����ڰ˹���Ы����ҿ���ס����\n"NOR,users());
             else
         message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
             "�����˵ڰ˹���Ы�������������ֹ�ǰ����\n"NOR,users());
if((ob&&ob->query("12gong/tiancheng")=="done") && (ob&&ob->query("12gong/tianxie")!="done"))
        {
			 ob->start_busy(3);
			 ob->set("12gong/tianxie","done");
             ob->add("12gong/number",1);
             ob->add("combat_exp", 10000);
             tell_object(ob,"��Ӯ����ʮ�����");

        }
       ::die();
}

void unconcious()
{
  die();
}
