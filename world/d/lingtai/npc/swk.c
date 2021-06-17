//tomcat 2000/03/05
// swk.c

#include <ansi.h>


inherit NPC;
inherit F_MASTER;

void create()
{
	set_name( HIW "�����" NOR, ({ "sun wukong", "wukong","swk"  }) );
	set("long",
		"һ��������ߣ����ݸɸɣ������ë�������\n");

	set("age", 30);
	
	set("max_gin", 8000);
	set("max_kee", 8000);
	set("max_sen", 8000);
        set("gin", 8000);
	set("kee", 8000);
	set("sen", 8000);

	set("max_force", 8000);
	set("force", 16000);
	set("max_mana", 8000);
	set("mana", 16000);
         set("force_factor", 350);
        set("mana_factor", 300);

	set("str", 100);
	set("cor", 100);
	set("cps", 100);
	set("spi", 100);
	set("int", 100);
	set("con", 100);
	set("kar", 100);
	set("per", 100);

	set("combat_exp", 10000000);
	set("daoxing", 10000000);

        
        set_skill("unarmed", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
	set_skill("stick", 300);
	set_skill("spells", 300);
	set_skill("dao", 300);
	set_skill("puti-zhi", 300);
        set_skill("sword", 300);
        set_skill("liangyi-sword", 300);
	set_skill("wuxiangforce", 300);
	set_skill("force", 300);
	set_skill("qianjun-bang", 300);
	set_skill("jindouyun", 300);
	
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
	set("fangcun/panlong_accept","done");
	set("fangcun/panlong_qiansi_finish",1);
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: cast_spell, "dingshen" :),
		(: cast_spell, "fenshen" :),
		(: perform_action, "stick","qiankun" :),
		(: perform_action, "stick","panlong" :),
        }) );

       set("title", HIR"�����ʥ"NOR);
	set("apply/attack", 100);
	set("apply/defense", 100);
	set("apply/armor", 100);
	set("apply/damage", 100);
        create_family("����ɽ���Ƕ�", 1, "��");
	setup();

	carry_object("/d/obj/weapon/stick/fake-jingubang.c")->wield();
	carry_object("/d/obj/cloth/shoupiqun.c")->wear();
}

void attempt_apprentice(object ob)
{
	ob=this_player();
	
        if( (string)ob->query("family/family_name")=="����ɽ���Ƕ�") {
	if ((int)ob->query("daoxing") < 1000000 ) {
  	command("say �����̫���ˡ�\n");
	return;
	}

	if( (int)ob->query("pending/kick_out")) {
	command("say ��λ" + RANK_D->query_respect(ob) + "����˵�˲�Ҫ������Ϊͽ�ˣ�\n");
	command("sigh");
	return;
	}

        if (ob->query("obstacle/number") < 26) {
	command("say ��λ" + RANK_D->query_respect(ob) + "����Ϊʦ��Ҫ��������ȡ�����ѣ�\n");
	command("sigh");
	return;
	}
	
	if( (int)ob->query_skill("dao", 1) < 180 ) {
	command("say ��λ" + RANK_D->query_respect(ob) + "���ҵ����ɷ���ỹ�������������Ҳ����Ϊ���ѣ��������գ�\n");
	command("sigh");
	return;
	}
        
        command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
        command("recruit " + ob->query("id") );
	return;
	}
        command("shake");
        command("say û�������ͬ�⣬�Ҳ�������Ϊͽ" + RANK_D->query_respect(ob) + "������Ѱ���˰ɣ�\n");
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "taoist");
ob->set("title", RED"�����ʥ�״�����"NOR);
}

