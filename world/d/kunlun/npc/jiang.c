inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("������", ({ "jiang ziya", "jiang", "ziya" }));
        set("title", "�ܳ���������");   
        set("long", @LONG
    �������У���Ԫʼ�����������ж��꣬�����ܳ�������º󷵻���
�ء�
LONG);
        set("gender", "����");
        set("age", 55);
        set("attitude", "peaceful");
        set("rank_info/self", "����");
        set("class", "shen");
    
    set("max_kee", 1000);
        set("max_gin", 600);
           set("max_sen", 1000);
        set("force", 2000);
        set("max_force", 1000);
        set("force_factor", 75);
        set("max_mana", 1000);
        set("mana", 2000);
        set("mana_factor", 55);
        set("combat_exp", 750000);

        set("eff_dx", 150000);
        set("nkgain", 300);

        set_skill("literate", 150);
       set_skill("unarmed", 150);
       set_skill("dodge", 160);
set_skill("mace", 180);
       set_skill("dashen-bian", 180);
       set_skill("force", 150);
       set_skill("parry", 150);
       set_skill("spells", 150);
       set_skill("yuxu-spells", 150);
       set_skill("kaitian-zhang", 150);
       set_skill("xuanzong-force", 150);
       set_skill("lingyunbu", 150);
       map_skill("spells", "yuxu-spells");
       map_skill("unarmed", "kaitian-zhang");
       map_skill("force", "xuanzong-force");
       map_skill("mace", "dashen-bian");
       map_skill("parry", "dashen-bian");
       map_skill("dodge", "lingyunbu");


        create_family("����ɽ���鶴", 2, "����");

        setup();
        carry_object("/obj/money/gold");
        carry_object("/d/kunlun/obj/dashenwhip")->wield();
}

void attempt_apprentice(object ob)
{
        if ((int)ob->query("daoxing") < 150000 ) {
        command("say ���ֵĵ��в���Щ������ô��ѧ�ҵı޷��أ���" + RANK_D->query_respect(ob) + "������Ŭ������ѧ���湦��\n");
                return;
        }
        command("nod");
        command("say ��λ�����п���֮�ţ��Ҿ�������ɡ�\n");
message("system", HIY"����ɽ���鶴�ֶ���һ������  "+this_player()->name()+HIW"
                     ����ɽ���鶴��������ǿ�ˡ�\n"NOR,users());
        command("recruit " + ob->query("id") );
        return; 
}
