int main(object me, string arg)
{
        mixed *ob;
        int i,j;
        string output;

        output = sprintf("%-20s %-6s %s\n", "名称", "ID","物件");
        if( arg && arg!="" )
        ob = objects( (: query_heart_beat :) );
        else
        ob = objects( (: query_heart_beat :) );

    j =sizeof(ob);
output += sprintf("总共有%d个物体\n", j);
if(j > 1000) j=1000;
        for(i=0; i<j; i++) {
                        output += sprintf("%10s : %15s : %20s\n",ob[i]->query("name"),ob[i]->query("id"),file_name(ob[i]));
        }

        me->start_more(output);
        return 1;
}


int help()
{
        write(@LONG
指令格式：checkob

查询心跳物品。

LONG
        );
        return 1;
}
