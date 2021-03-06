inherit NPC;
inherit F_MASTER;
#include <ansi.h>
string ask_pozhen();
void create()
{
       set_name(HIW"元始天尊"NOR, ({"yuanshi tianzun","tianzun", "master"}));
       set("long", "昆仑玉虚洞祖师爷，满头白发的老人，两眼炯炯有神。\n");
       set("title", HIW"道法"NOR);
       set("gender", "男性");
       set("age", 100);
        set("class", "shen");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "老师祖");
       set("per", 40);
       set("int", 30);
       set("max_kee", 5000);
       set("max_gin", 1000);
       set("max_sen", 5000);
       set("force", 6000);
       set("max_force", 6000);
       set("force_factor", 150);
       set("max_mana", 6000);
       set("mana", 6000);
       set("mana_factor", 150);
       set("combat_exp", 10000000);
        set("daoxing", 10000000);

       set_skill("spells",300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("xuanzong-force", 300);
        set_skill("lingyunbu", 300);
        set_skill("dashen-bian", 300);
        set_skill("kaitian-zhang", 300);
        set_skill("huntian-jian", 300);
        set_skill("literate", 300);
        set_skill("unarmed", 300);
        set_skill("yuxu-spells", 300);
        set_skill("wugou-jian", 300);
        set_skill("mace",300);
        map_skill("spells", "yuxu-spells");
        map_skill("dodge", "lingyunbu");
        map_skill("mace", "dashen-bian");
        map_skill("force", "xuanzong-force");
        map_skill("parry", "wugou-jian");
        map_skill("sword", "huntian-jian");
        map_skill("unarmed", "kaitian-zhang");
        set("chat_chance_combat", 90);
	   set("chat_msg_combat", 
	   ({
	     (: perform_action, "unarmed","po" :),
	     (: perform_action, "sword","xue" :),
	     (: perform_action, "sword","lin" :),
	     (: perform_action, "sword","feixian" :),
	    }) );
        set("inquiry",([
      "驱神逐魔": (: ask_pozhen :),
      ]));
create_family("昆仑山玉虚洞", 1, "蓝");
setup();

        carry_object("/d/lingtai/obj/shoe")->wear();
        carry_object("/d/kunlun/obj/zhuxian")->wield();
}

void attempt_apprentice(object ob)
{       ob=this_player();
        if( (string)ob->query("family/family_name")=="昆仑山玉虚洞") {
        if ((int)ob->query("daoxing") < 500000 ) {
        command("say 欲想成仙，道兄的道行是不是差了点？，" + RANK_D->query_respect(ob) + "还需多加努力才能早悟大道。\n");
        return;
        }
/*
        if( (int)ob->query("pending/kick_out")) {
        command("say 这位" + RANK_D->query_respect(ob) + "反复无常，老夫不原再收你为徒了！\n");
        command("sigh");
        return;
        }
*/
        if ((int)ob->query_int() < 35) {
        command("say 这位" + RANK_D->query_respect(ob) + "悟性太低，恐怕收了你也难有作为！\n");
        command("sigh");
        return;
        }
        if( (int)ob->query_skill("yuxu-spells", 1) < 150 ) {
        command("say 这位" + RANK_D->query_respect(ob) + "对我玉虚仙法领会还不够深，现在收你你也很难领悟我的讲解，不如作罢！\n");
        command("sigh");
        return;
        }
        command("smile");
        command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
       command("recruit " + ob->query("id") );
       ob->set("title", "元始天尊嫡传弟子"); 
    message("system", HIY"昆仑山玉虚洞又多了一个弟子  "+this_player()->name()+HIW"
                     昆仑山玉虚洞的势力加强了。\n"NOR,users());
        return;
        }
        command("shake");
        command("say 老夫不收外门弟子，" + RANK_D->query_respect(ob) + "还是另寻他人吧！\n");
        return;
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "shen");
}

int accept_fight(object me, object ob)
{       ob=this_player();
        command("say " + RANK_D->query_rude(ob) + "杀心太重，恐祸不久已！\n");
        return 0;
}
void die()
{

        if( environment() ) {
        message("sound", "\n\n元始天尊微皱眉头，道：这家伙这么厉害，也罢！！！\n\n", environment());
        command("sigh");
        message("sound", "\n元始天尊身形一转，架起一朵莲花飞上天空。。。\n\n", environment());
        }

        destruct(this_object());
}
string ask_pozhen()
{
	object me=this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法学习驱神逐魔。\n");
	if(me->query("family/family_name") != "昆仑山玉虚洞" )
                return ("你不是我昆仑弟子，无法学习驱神逐魔!!\n");
        if(me->query("quzhu_cant"))
      		return ("你的机缘不够，无法学习驱神逐魔！");
        if( me->query("quzhu_known") > 2 )
      		return ("驱神逐魔的法诀你都已经知道了，把机会留给别人吧！");
	me->set_temp("quzhu/learn",1);
	message_vision(HIW"只见$N"+HIW"身上飘下一朵白莲，缓缓落在$n"+HIW"身上！\n"NOR, this_object(),me);
	command("say 我赐你一朵白莲，自然就不怕阵中守卫的禁制！");
	return ("我正在全力破除十绝阵，你去阵中找我分身，问一下破阵之事吧！");
}