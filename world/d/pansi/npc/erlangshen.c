#include <ansi.h>
inherit NPC;
int handle_kill(object me);

void create()
{
        set_name("�������", ({"erlang zhenjun", "erlang", "zhenjun"}));
        set("long", "���ǳ���ѻ�Ӣ��ʥ���Ի��ޱߺŶ��ɡ�
�����˹�����Զ�����÷ɽ��ʥ�С�\n");
	set("looking", "�����忡ò���ã���������Ŀ�й⡣");
        set("age", 28);
        set("attitude", "peaceful");
        set("gender", "����");
        set("title", "�ѻ�������");
        set("str", 40);
        set("int", 40);
        set("per", 30);
	set("con", 30);
       set("max_kee",8000);
        set("max_sen", 8000);
        set("combat_exp", 15000000);
        set("daoxing", 20000000);

        set("force", 8000);
        set("max_force", 8000);
        set("mana", 16000);
        set("max_mana", 8000);
        set("force_factor", 200);
        set("mana_factor", 200);

        set("eff_dx", 800000);
        set("nkgain", 800);

        set_skill("unarmed", 350);
	set_skill("force", 350);
	set_skill("spells", 350);
       set_skill("parry", 450);
       set_skill("dodge", 450);
       set_skill("spear", 450);
       set_skill("dao",350);
       set_skill("huomoforce",350);
	set_skill("moyun-shou", 350);
	set_skill("moshenbu", 450);
       set_skill("bawang-qiang", 450);
       set_skill("mace", 350);
       set_skill("wusi-mace", 350);
       map_skill("mace","wusi-mace");  
	map_skill("unarmed", "moyun-shou");
	map_skill("dodge", "moshenbu");
       map_skill("spear","bawang-qiang");
       map_skill("parry", "bawang-qiang");
       map_skill("force","huomoforce");
       map_skill("spells","dao");
       set("chat_chance_combat", 50);
       set("chat_msg_combat", ({
                  (: perform_action, "unarmed", "zhangxinlei" :), 
       }) );
       set("inquiry", ([ /* sizeof() == 4 */
  		"here" : "�ҷ������ּ����Ҫ׽����ϼ����ϼ���ˡ�",
  		"name" : "���˶����������Ҳ��",
	]) );

        setup();
        carry_object("/d/meishan/npc/obj/spear")->wield();
        carry_object("/d/obj/armor/jinjia")->wear();
        carry_object("/d/obj/drug/jinchuang")->set_amount(random(10));
}

void init()
{
	object me=this_object();
	object who=this_player();

	add_action("do_kill", "kill");
	return ::init();
}
		     
void die()
{
	int dx,dx1,wx,qn;
	object who;
	object me=this_object();
    who=present(me->query("killer"),environment());
if (!who) return 0;
	dx=(who->query("daoxing"))/20;
if (dx>=100000) dx=100000;
	dx1=dx/1000;
	wx=(who->query("combat_exp"))/20;
if (wx>=10000) wx=10000;
	qn=30000;
    
  	if (!who->query_temp("give_suo"))
	  return ::die();
   if ((!present("qingxia xianzi"))&&(!present("zixia xianzi")))
	{
	   who->delete("fangcun/panlong_nowaypansi");
	   return ::die();
	}
   message("sound", "\n\n\n������ŭ������ĪҪ���񣬴��ҵ��������������״ȥ��\n",environment());
   message("sound", "\n��������ϰ��ƣ���������ɽ��ȥ������\n\n",environment());
   if (present("xiaotian quan"))
  {    
     message("sound", "Х��ȮҲ���Ŷ�����������ȥ��\n\n", environment());
     destruct(present("xiaotian quan"));
  }
   message_vision(WHT"\n\n��ϼ�����������˵���ϼ��������������ϼ����������˵����\n"NOR, who);
   message_vision(WHT"\n           ��Ҳֻ������ôһ�����ã����ǲ�Ҫ�ٶ���ȥ�ˣ��������Ѿ�ȥ���������״ȥ
        �ˣ�����Ҳ�ûص����������������о�ˣ����������˻�Ҫ����"+RANK_D->query_respect(who) + "��������֣�\n"NOR, who);
   message_vision(HIM"\n\n\n��ϼҲ������������ϼ����ֹ��ס����ˮ�Ѿ�����������\n"NOR, who);
   message_vision(HIM"\n           �⳾���Ѿ�û��ʲô���������ˣ���㣬�����ߣ�\n\n\n"NOR, who);
   message_vision("\n��ϼ�������˵���ϼ�����˶���$N������л�������ͷ��������ɽȥ�ˣ�\n"NOR, who);
   message_vision(HIY"\n\n\n$N���컹��Ŀ�Ͷ��˽���Զȥ��һ��˵��������ζӿ����ͷ������������\n"NOR, who);
   destruct(present("qingxia xianzi"));
   destruct(present("zixia xianzi"));
   message_vision(HIM"\n\n\n�������������ϼ��������"+who->query("name")+RANK_D->query_respect(who) + "��̨����֮�£�ˡ�Ҳ���ǰ�����أ���" + RANK_D->query_respect(who) + "��������ʦ���������ˣ�\n\n\n\n"NOR,who);
		who->add("fangcun/panlong_visite",1);
		who->set("fangcun/panlong_pansi","done");
		who->delete("fangcun/panlong_nowaypansi");
 message("chat",HIC+"��"+HIW+"��������"+HIC+"����������(Rulai fo)��"+who->query("name")+"�����������ȴǧ��Թ�ޣ�����ҷ𣬵��湦������Ҳ��\n"NOR,users());
        message("chat",HIC+"��"+HIW+"��������"+HIC+"����������(Rulai fo)��"+who->query("name")+"�õ�����������"+chinese_number(dx1)+"�꣬��ѧ"+wx+"�㣬Ǳ��30000�㣮\n"NOR,users());
	who->add("daoxing",dx);
	who->add("combat_exp",wx);
	who->add("potential",30000);
	    if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
		who->set("guanli/pansi",1);
   destruct(this_object());
   return;
}

void unconcious()
{
 call_out("die",1);
}

int do_kill(string arg)
{
    if(!id(arg)) return 0;
    handle_kill(this_player());
    return 0;
}
int handle_kill(object me)
{
    if (me->query("fangcun/panlong_nowaypansi"))
  {
	  set_skill("unarmed", 200);
	set_skill("force", 200);
	set_skill("spells", 200);
       set_skill("parry", 200);
       set_skill("dodge", 200);
       set_skill("spear", 200);
       set_skill("dao",200);
       set_skill("huomoforce",200);
	set_skill("moyun-shou", 200);
	set_skill("moshenbu", 200);
       set_skill("bawang-qiang", 200);
       set_skill("mace", 200);
       set_skill("wusi-mace", 200);
       set("force_factor", 1);
        set("combat_exp", 1500000);
        set("daoxing", 3000000);
        set("mana", 4000);
        set("max_mana", 5000);
	   this_object()->set("killer",me->query("id"));
  }
}

