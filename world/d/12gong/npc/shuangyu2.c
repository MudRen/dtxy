// by happ@YSZZ

 
inherit NPC;
#include "star.h" 
void create()
{
        set_name("�����޵�", ({"aphrodite two"}));
        set("long", "�ų���������ʥ��ʿ������õ��Ϊ������Ҳ�ǱȽ�а��Ļƽ�ʥ
��ʿ������ڤ��֮ս����Ϊ�ŵ������� �ػ���˫����.\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",45);
        set("per",30);
        set("str",63);
        set("int",64);
        set("combat_exp",8000000);
        set("chat_chance",20);
        set_skill("dodge", 330);
        set_skill("force", 330);
        set_skill("parry", 330);
        set_skill("unarmed", 330);
        set_skill("sword", 330);
        set_skill("westsword",330);
        set_skill("boxing",330);
        set_skill("balei",330);
        set_skill("spells",330);
        set_skill("shuangyu", 330);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","shuangyu");
        map_skill("dodge","balei");
        set("max_force", 6500);
        set("force", 12000);
        set("max_mana",6000);
        set("mana",12000);
        set("mana_factor",230);
        set("force_factor", 200);
        set("max_kee", 5000);
        set("max_gin", 5000);
        set("max_sen", 5000);

        setup();
        carry_object(__DIR__"obj/sy_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}
 
void init()
{
        remove_call_out("check_me");
        call_out("check_me",12);
}
void check_me()
{
        command_function("say ������һ����!\n");
        destruct(this_object());
}
