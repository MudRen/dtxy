// tomcat
 
#include <ansi.h>

inherit NPC;
string ask_jueqing();
void create()
{
  set_name(HIR"̫����"NOR, ({"taiyang shen", "sun"}));
   
  set("gender", "����");
  set("age", 430);
  set("str", 100);
  set("per", 35);
  set("int", 30);
  set("cor", 50);
  set("cps", 40);
  set("combat_exp", 10000000);
  set_skill("spear", 600);
  set_skill("force", 600);
  set_skill("dodge", 600);
  set_skill("parry", 600);
  set_skill("unarmed", 600);
  set_skill("huoyun-qiang", 600);
  set_skill("literate", 600);
  set_skill("spells", 600);
  set_skill("pingtian-dafa", 600);
  set_skill("moshenbu", 600);
  set_skill("huomoforce", 600);
  set_skill("moyun-shou", 600);
  map_skill("force", "huomoforce");
  map_skill("spells", "pingtian-dafa");
  map_skill("unarmed", "moyun-shou");
  map_skill("spear", "huoyun-qiang");
  map_skill("parry", "huoyun-qiang");
  map_skill("dodge", "moshenbu");
  set("max_sen", 10000);
  set("max_kee", 10000);
set("force", 18000);
set("max_force", 9000);
set("mana",18000);
set("max_mana",9000);
set("daoxing",10000000);
set("force_factor", 450);
set("mana_factor", 451);
  set("chat_chance_combat", 80);
  set("chat_msg_combat", ({
		(: perform_action, "spear", "lihuo" :),
  }) );
 set("inquiry",([
      "����": (: ask_jueqing :),
      ]));
  set("family/family_name","���ƶ�");
  setup();
 
  carry_object("d/obj/weapon/spear/huomoqiang")->wield();
  carry_object("/d/obj/armor/jinjia")->wear();
}


string ask_jueqing()
{
	object me=this_player();
	if( me->query("can_go_sun") )
	{
		me->delete("can_go_sun");
		if( random(me->query("kar")) > 20 )
		{
			message_vision("\n$N��$n˵����Ȼ����˳��ģ��պ�������Ҫ����һ������������\n",this_object(),me);
			me->set("accept/sun",1);
		}
		else
			message_vision("\n$N��$n˵������Ե�ֲ������պ���Ҫ����Ϊ֮��\n",this_object(),me);
		message_vision("\n$NҲ���ٶ�˵��һ����$n���κ����������ϳǿ�ջ��\n",this_object(),me);
		me->move("/d/city/kezhan");
		return ("���²������ס�����");
	}
      	if( !me->query_temp("jueqing/sun") )
      	{
	      	me->move("/d/city/kezhan");
	      	return("������ô�������ģ���");
	}
	else
	{
		command("sigh");
		me->set_temp("jueqing/sun",2);
		command("say ��ʱ���Ǽ����ֵ����Ժ�Ϊ�����²������ѣ���ŭ����ۡ�");
		message_vision("$N˵����������۴ͺ���������������ĸ���϶�Ϊ���ӣ������칬�ط���\n",this_object());
		message_vision("$N˵�����ٺ����϶�����һ�㣬��������������������˾���֮�⡣\n",this_object());
		message_vision("$N˵������ʱ�϶�һ�������ѩ�����������������������֮�п��������ܱȡ�\n",this_object());
		message_vision("$N˵������ʱ���Ƕ������ˣ������϶������ն̣����ǵ��ǲ��¡�\n",this_object());
		message_vision("$N˵����˭֪�϶����Թ��ˣ����ʸ������ڳ��ˣ����������¾������ͬʱ�������칬��ҩ��Ϊͻ���ͽ���ʵ���Ѿ��������������ˡ�\n",this_object());
		message_vision("$N˵�����϶�ӽ����裬������ս��նɱ���Ұ˸��ܵܡ�ֻ��ÿ�����ӽ�һ�Σ��ұ㰮��һ�֡�\n",this_object());
		message_vision("$N˵���������ߵ�����ǰ��ʱ���Ѿ�������ս�ˣ�ֻҪ��һ����������ɱ������Ϊ�Ұ˸��ܱܵ���\n",this_object());
		message_vision("$N˵����ֻ�ǣ�ֻ�ǣ������ջ����²����֣������ҽ����͵����¹�����������ĸ���š�\n",this_object());
		message_vision("$N˵������Ȼ���������ڳ��ˣ��������ǵ���ΪҲ���������������������˾������Ļ𶾣�Ҳֻ���¹�������������ȥ�ˡ�\n",this_object());
		message_vision("$N˵������ǧ�궼��ȥ�ˣ�Ҳ��֪������ô���ˡ�\n",this_object());
		me->command("say �ҵõ��˱��꣬����϶���������Ѿ����˰ɡ�");
		message_vision("$N˵�����Ǿͺã��������Ƕ��½��������ô����˺��������ڲ��õ���������\n",this_object());
		if( random(me->query("kar")) > 20 )
		{
			message_vision("\n$N��Ĭ��һ�ᣬͻȻ��$n˵���պ��������Ҫ��æ���ռ����պ���һ���������ڸ�������������һ��֮����\n",this_object(),me);
			me->set("accept/sun",1);
		}
		message_vision("$N˵������֪������о�����֪������ľ���������������ȶ������岻�ã��һ�����������ȥ�ɡ�\n",this_object());
		message_vision("$N˵������ǧ���ˣ���һֱ������Щ����ĺ��ۣ�����˵���������ɶ��ˣ���Ҫ��л���ˡ�\n",this_object());
		message_vision("$N˵�������������������������ף���ɣ�\n",this_object());
		message_vision("\n$NҲ���ٶ�˵��һ����$n���κ����������ϳǿ�ջ��\n",this_object(),me);
		me->move("/d/city/kezhan");
		return ("���²������ס�����");
	}
}