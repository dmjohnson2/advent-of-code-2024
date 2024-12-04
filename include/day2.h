#ifndef DAY_2_H
#define DAY_2_H

typedef enum _safety
{
	SAFE,
	UNSAFE
} Safety;

typedef struct _report_node
{
	int data;
	struct _report_node *next;
} ReportNode;

typedef struct _report
{
	int count;
	Safety safety;
	ReportNode *head;
} Report;

#endif
