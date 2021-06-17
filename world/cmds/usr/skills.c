// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

string *skill_level_desc = ({
		BLU "��ѧէ��" NOR,
		BLU "��֪����" NOR,
		BLU "��֪����" NOR,
    BLU "��ͨƤë" NOR,
		HIB "��ʶ֮��" NOR,
		HIB "�����ž�" NOR,
		HIB "��������" NOR,
		HIB "��������" NOR,
		YEL "������" NOR,
		YEL "ƽ������" NOR,
		YEL "ƽƽ����" NOR,
		YEL "é���ٿ�" NOR,
		HIY "�ᳵ��·" NOR,
		HIY "������ͨ" NOR,
		HIY "�������" NOR,
		HIY "����ǳ��" NOR,
		HIM "��������" NOR,
		HIM "��������" NOR,
		HIM "�������" NOR,
		HIM "�������" NOR,
		HIR "����С��" NOR,
		HIR "����Ѿ�" NOR,
		HIR "����似" NOR,
		HIR "�������" NOR,
		MAG "׿����Ⱥ" NOR,
		MAG "����似" NOR,
		MAG "�����ɵ�" NOR,
		MAG "�����뻯" NOR,
		CYN "��Ⱥ����" NOR,
		CYN "��Ȼ��ͨ" NOR,
		CYN "�Ƿ��켫" NOR,
		CYN "׿Ȼ���" NOR,
		HIC "һ����ʦ" NOR,
		HIC "��������" NOR,
		HIC "������˫" NOR,
		HIC "��ǰ����" NOR,
		WHT "���ž���" NOR,
		WHT "������" NOR,
		WHT "������ʥ" NOR,
		WHT "��豹���" NOR,
		HIW "��ɲ�" NOR
	});

string *knowledge_level_desc = ({
		BLU "��ѧէ��" NOR,
		BLU "��������" NOR,
    BLU "��֪����" NOR,
		HIB "ƽ������" NOR,
		HIB "˾�ռ���" NOR,
		HIB "�����ž�" NOR,
		YEL "��֪һ��" NOR,
		YEL "é���ٿ�" NOR,
		YEL "��ʶ֮��" NOR,
		HIY "��������" NOR,
		HIY "������" NOR,
		HIY "�ᳵ��·" NOR,
		HIM "��������" NOR,
		HIM "������ͨ" NOR,
		HIM "����ǳ��" NOR,
		HIR "����С��" NOR,
		HIR "�������" NOR,
		HIR "��Ȼ����" NOR,
		MAG "����ʶ��" NOR,
		MAG "������ͨ" NOR,
		MAG "׿����Ⱥ" NOR,
		CYN "��������" NOR,
		CYN "��Ȼ��ͨ" NOR,
		CYN "����ͨ��" NOR,
		HIC "������" NOR,
		HIC "��Ⱥ����" NOR,
		HIC "������˫" NOR,
		WHT "��������" NOR,
		WHT "������" NOR,
		WHT "������ʥ" NOR,
		HIW "��ɲ�" NOR
});

string skill_level(string, int);

int main(object me, string arg)
{
	object ob, *list, couple_ob;
	mapping skl, lrn, map;
	string *sname, *mapped,target,cardname;
	int i, marry_flag;

	seteuid(getuid());

	if(!arg)
		ob = me;
	else{
		ob = present(arg, environment(me));
		if (!ob) ob = find_player(arg);
		if (!ob) ob = find_living(arg);
                if (!ob) ob = LOGIN_D->find_body(arg);
                if (!ob || !me->visible(ob))
                return notify_fail("��Ҫ�쿴˭�ļ��ܣ�\n");
	}

	target = (string) me->query("couple/couple_id");
	if(stringp(target)) couple_ob = find_player(target);
	if( ob!=me && !wizardp(me) && !ob->is_apprentice_of(me)
	&& !me->is_apprentice_of(ob) && ob!=couple_ob
	&& !ob->query("skill_public") && !ob->is_manmade_npc())
		return notify_fail("ֻ�й������ʦͽ��ϵ�����ܲ쿴���˵ļ��ܡ�\n");

	skl = ob->query_skills();
	if(!sizeof(skl)) {
		write( (ob==me ? "��" : ob->name()) + "Ŀǰ��û��ѧ���κμ��ܡ�\n");
		return 1;
	}
	write( (ob==me ? "��" : ob->name()) +"Ŀǰ��ѧ��"+
chinese_number(sizeof(skl))+"�ּ��ܣ�\n\n");
	sname  = sort_array( keys(skl), (: strcmp :) );

	printf(HIC"�ԡԩ����������������������������������������������������������������ԡ�\n"NOR);
	map = ob->query_skill_map();
	if( mapp(map) ) mapped = values(map);
	if( !mapped ) mapped = ({});

	lrn = ob->query_learned();
	if( !mapp(lrn) ) lrn = ([]);

	for(i=0; i<sizeof(skl); i++) {
		printf("%s%s%-40s ��%-10s��  %3d/%5d\n",
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": "��"),
			to_chinese(sname[i]) + " (" + sname[i] + ")"NOR,
			skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
			skl[sname[i]], (int)lrn[sname[i]],
		);
	}
        printf(HIC"\n�ԡԩ�����������������������"BLINK""HIG"��������Ρ�"NOR""HIC"-�������������������������ԡ�\n"NOR);
	return 1;
}

string skill_level(string type, int level)
{
	int grade;

	grade = level / 10;

	switch(type) {
		case "knowledge":
			//if( grade >= sizeof(knowledge_level_desc) )
			//	grade = sizeof(knowledge_level_desc)-1;
			//return knowledge_level_desc[grade];
			if( grade >= sizeof(skill_level_desc) )
				grade = sizeof(skill_level_desc)-1;
			return skill_level_desc[grade];
		default:
			if( grade >= sizeof(skill_level_desc) )
				grade = sizeof(skill_level_desc)-1;
			return skill_level_desc[grade];
	}
}
string pet_skill(object ob)
{
	string desc;
        object  *list, couple_ob;
        mapping skl, lrn, map;
        string *sname, *mapped,target,cardname;
        int i, marry_flag;
        skl = ob->query_skills();
        if(!sizeof(skl)) {
                desc =  ob->name() + "Ŀǰ��û��ѧ���κμ��ܡ�\n";
                return desc;
        }
        	desc =  ob->name() +"Ŀǰ��ѧ���ļ��ܣ�\n\n";
        sname  = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        lrn = ob->query_learned();
        if( !mapp(lrn) ) lrn = ([]);



      for(i=0; i<sizeof(skl); i++) {
		printf("%s%s%-40s" NOR " - %-10s %4d/%5d\n",
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": "��"),
			to_chinese(sname[i]) + " (" + sname[i] + ")",
			SKILL_D(sname[i])->level_description(skl[sname[i]]),
			skl[sname[i]], (int)lrn[sname[i]],

                );
        }
        return desc +"\n";
}
int help(object me)
{
	write(@HELP
ָ���ʽ : skills [<ĳ��>]

���ָ����������ѯ��ѧ���ļ��ܡ�

��Ҳ����ָ��һ��������ʦͽ��ϵ�Ķ����� skills ���Բ�֪�Է��ļ���״����


HELP
    );
    return 1;
}

