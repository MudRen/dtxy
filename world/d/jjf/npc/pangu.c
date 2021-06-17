// pangu.c �̹�
//lestat
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string jiebai();
string unjiebai();
string ask_kai();
void create()
{
        set_name(HIR"�̹�"NOR, ({ "pan gu","gu" }) );
        set("title", HIR"����ٵ�"NOR);
        set("gender", "����" );
        set("age", 44);
        set("str", 100);
        set("cor", 30);
        set("cps", 30);
        set("int", 30);
        set("per", 30);
        set("kar", 60);
        set("long",
                "�Ϲ�����,����ٵ�!\n");
        set("max_force", 15000);
        set("force", 15000);
        set("force_factor", 120);
        set("combat_exp", 10000000);
        set("daoxing", 10000000);
        set("attitude", "friendly");
        set("max_kee", 18000);
        set("max_sen", 18000);
        set_skill("parry", 300);
        set_skill("dodge", 300);
        set_skill("force", 300);
        set_skill("archery", 300);
        set_skill("literate", 300);
        set_skill("mace", 300);
        set_skill("unarmed", 300);
        set_skill("changquan", 300);
        set_skill("yanxing-steps", 300);
        set_skill("lengquan-force", 300);
        set_skill("spear", 300);
        set_skill("axe", 300);
        set_skill("baguazhou", 300);
        set_skill("spells", 300);
        set_skill("sanban-axe", 300);
        set("max_mana", 10000);
        set("mana", 15000);
        set("mana_factor", 450);
        map_skill("force", "lengquan-force");
        map_skill("unarmed", "changquan");
        map_skill("spells", "baguazhou");
        map_skill("axe", "sanban-axe");
        map_skill("parry", "sanban-axe");
        map_skill("dodge", "yanxing-steps");
        
        set_temp("apply/damage",300);
        set_temp("apply/armor",600);
        set("kai_known",3);
        set("chat_chance_combat", 90);
        set("chat_msg_combat", 
   	({
     		(: perform_action, "axe", "kai" :),
     		(: perform_action, "axe", "sanban" :),
    	}) );
        set("inquiry",([
      			"����ٵ�": (: ask_kai :),
      			]));
        create_family("������", 1, "��");
        setup();
        carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/npc/obj/axe")->wield();
        
}



int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
    ob->set("class", "fighter");
    ob->set("title", HIR"�̹Ź�����"NOR);
}

void attempt_apprentice(object ob)
{
        ob=this_player();
  
  if (ob->query("obstacle/number") < 26) {
        command("say ��λ" + RANK_D->query_respect(ob) + "�㽭������̫ǳ�ˣ�\n");
        command("sigh");
        return;
        }
 if( (int)ob->query("pending/kick_out")) {
        command("say ��λ" + RANK_D->query_respect(ob) + "�Ϸ�ƽ����޲��Ҳ���֮�ˣ�\n");
        command("heng");
        return;
        }
  if (ob->query("combat_exp") < 1000000)
    {
       command("sigh");
       command("say ��λ" + RANK_D->query_respect(ob) + "���书����̫���ˣ�\n");
       return ;
     }
    command("haha");
    command("recruit " + ob->query("id") );
    return 0;
}

string ask_kai()
{
	object me = this_player();
	object downroom = load_object(__DIR__"wuxing");
	if( !wizardp(me) && me->query("family/family_name") != "������" )	
		return ("�����ҽ��������ӣ�");
	if( me->query("betray/count") )
		return ("�����Ķ����޷���Ὺ��ٵؾ�ѧ��\n");
	if( me->query("kai_known") > 2 )
		return ("�⿪��ٵصĵ����㶼���ˣ������Ҫ�����Լ����ˣ�");
	if( me->query("kai_cant") )
		return ("��ѧ���㶼ѧ���ˣ�����ѧ�ģ���Ҳ��᲻�ˣ�ĪҪǿ��");
	if( !me->query("kai_known"))
	{
		if( me->query_skill("literate",1) < 200 )
			return ("�������ѧʶ������ܶ��ÿ���ٵأ�");
		if( me->query_skill("sanban-axe",1) < 200 )
			return ("�㸫���õĲ�����������");
		if( me->query_skill("lengquan-force",1) < 200 )
			return ("���ڹ�̫�ͣ�");
	}
	if(me->query("kai_known")==1)
	{
		if( me->query_skill("literate",1) < 250 )
			return ("Ҫ��һ����Ὺ��ٵأ������ѧʶ��������");
		if( me->query_skill("sanban-axe",1) < 250 )
			return ("�㸫���õĲ�����������");
		if( me->query_skill("lengquan-force",1) < 250 )
			return ("���ڹ�̫�ͣ�");	
	}
	if(me->query("kai_known")==2)
	{
		if( me->query_skill("literate",1) < 300 )
			return ("Ҫ��һ����Ὺ��ٵأ������ѧʶ��������");
		if( me->query_skill("sanban-axe",1) < 300 )
			return ("�㸫���õĲ�����������");
		if( me->query_skill("lengquan-force",1) < 300 )
			return ("���ڹ�̫�ͣ�");	
	}
	me->set_temp("kai_learn",1);
	command("say �ã�����������ᵽ����ٵصľ��衣");
	message_vision(HIW "�̹ŻӶ���˲����$N�����������£��ж���$N����Χ�������ϵ��\n" NOR, me);
	me->move("/d/jjf/hundun");
	tell_object(me,"����߳����̹ŵ������������������ĵط����統�����ƿ��Ļ��磬�ú�����������(lingwu)һ�°ɣ�\n");
	return ("�����ѧ��Ҫ��Ź���ˣ�");
}