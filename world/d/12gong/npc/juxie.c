inherit NPC;
#include "star.h"
 
void create()
{
        set_name("��˹��˹��", ({"death mask","mask","ju xie"}));
        set("long", "��з���ƽ�ʥ��ʿ������޳ܵĻƽ�ʥ��ʿ��ɱ������������ɱ
ͯ�����ɣ�����������Թ��������Լ�����ļ�ʬ��ڤ�粨�б�������ܡ�����ڤ��֮ս
����Ϊ�ŵ�������\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",30);
        set("spi",40);
        set("per",30);
        set("str",25);
        set("int",35);
          set("combat_exp",8000000);
        set("daoxing",8000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "��˹��˹��˵������֪��ʱ���ټ����ŵ��ȣ�\n"   
        }));
       set("attitude", "aggressive");
        set_skill("dodge", 250);
        set_skill("force", 250);
        set_skill("parry", 250);
        set_skill("unarmed", 250);
        set_skill("sword", 250);
        set_skill("westsword",250);
        set_skill("boxing",250);
        set_skill("balei",250);
        set_skill("spells",250);
        set_skill("jinniu", 250);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","jinniu");
        map_skill("dodge","balei");
        set("max_force", 3000);
        set("force", 6000);
        set("max_mana",3000);
        set("mana",6000);
        set("mana_factor",50);
        set("force_factor", 50);
        set("max_kee", 2000);
        set("max_gin", 2000);
        set("max_sen", 2000);

        setup();
        carry_object(__DIR__"obj/jx_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}
 
void check()
{
        object ob=this_object();
        object me=query_temp("my_killer");
        if( ! me ) return ;
   if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }                               
 if( me->is_ghost() )
     {
     remove_call_out("check");
     return;
     }

     switch(random(6))

     {        
        case 0:
        {
        message_vision(HIR"$N�߾�˫�֣�$n����ǰ��Ȼ������ڤ���Ȫ·��\n",ob,me);

        if(random(3)==0)

                {
              message_vision(HIR"$N����˹��˹�˻��У����ˤ��ڤ�綴Ѩ�У�\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(HIR"��һ����Ц���㿪��������֮��Ѩ��\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(HIR"$N������գ�ʹ��[��ʬ��ڤ�粨]$n��$N��С��������˻�Ȫ��ڣ�\n",ob,me);

        if(random(3)==0)

                {
              message_vision(HIR"��$Nɱ����ԩ���ӵ�����㣬������ϱ����˼�����Ѫ�ڣ�\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIR"��ǿ��ȫ������,��ɢ��[��ʬ��ڤ�粨]��\n"NOR,me);
        }
        break;

        case 2:
        {

        message_vision(HIR"$N�������һֻ��з�������������$n����ǰ��\n",ob,me);
                              
        if(random(3)==0)

                {
              message_vision(HIR"��з���һ˫����ǯ����ס���㣡\n"NOR,me);
              me->start_busy(3);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIR"$N����һ����ԭ���Ǹ�����\n"NOR,me,ob);
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

        if((ob&&ob->query("12gong/shuangzi")=="done") &&(ob&&ob->query("12gong/juxie")!="done"))
        {
        ob->start_busy(3);
        message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
        "�����˵��Ĺ���з����������ƽ�սʿǰ����\n"NOR,users());
        ob->set("12gong/juxie","done");
        ob->add("12gong/number",1);
        ob->add("combat_exp", 10000);
        tell_object(ob,"��Ӯ����ʮ�����");

        }
       message_vision(HIC"\n\n\n���ŵ�˹��˹�˵�����, ��Щ��������ɱ�������꽥���뿪�˾�з��.\n"NOR,ob);
	   ::die();
}

void unconcious()
{
  die();
}