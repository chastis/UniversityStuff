using System;
using System.Collections.Generic;
using System.Globalization;
using HtmlTags;
using Microsoft.AspNetCore.Mvc.ViewFeatures;

namespace Lab9_5
{
    public class HtmlBuilder
    {
        private readonly string _path;
        private HtmlDocument _html;

        private HtmlTag _table;

        public HtmlBuilder(string path)
        {
            this._path = path;
        }

        public HtmlBuilder CreateHtml()
        {
            _html = new HtmlDocument();
            return this;
        }

        public HtmlBuilder AddHead()
        {
            var link = new HtmlTag("link").Attr("rel", "stylesheet").Attr("href", "style.css");

            _html.Head.Children[0].Text("Reporting Page");
            _html.Head.Append(link);
            return this;
        }

        public HtmlBuilder CreateTable()
        {
            _table = new HtmlTag("table");

            var tableHeading = new HtmlTag("tr");

            tableHeading.Append(new HtmlTag("th").Text("Matrix size").Attr("rowspan", "3"));
            tableHeading.Append(new HtmlTag("th").Text("Sequential algorithm").Attr("rowspan", "3"));
            tableHeading.Append(new HtmlTag("th").Text("Parallel algorithm").Attr("colspan", "4"));

            _table.Append(tableHeading);

            var processorsNumber = new HtmlTag("tr");
            processorsNumber.Append(new HtmlTag("th").Text("2 processes").Attr("colspan", "2"));
            processorsNumber.Append(new HtmlTag("th").Text("4 processes").Attr("colspan", "2"));

            _table.Append(processorsNumber);

            var parameters = new HtmlTag("tr");

            for (var i = 0; i < 2; i++)
            {
                parameters.Append(new HtmlTag("th").Text("Time"));
                parameters.Append(new HtmlTag("th").Text("Acceleration"));
            }

            _table.Append(parameters);

            return this;
        }

        public HtmlBuilder AddResult(int matrixSize, double sequentialTime, List<KeyValuePair<double, double>> results)
        {
            var tr = new HtmlTag("tr");
            tr.Append(new HtmlTag("td").Text(matrixSize.ToString()));
            tr.Append(new HtmlTag("td").Text(sequentialTime.ToString(CultureInfo.InvariantCulture)));

            foreach (var (key, value) in results)
            {
                tr.Append(new HtmlTag("td").Text(key.ToString(CultureInfo.InvariantCulture)));
                tr.Append(new HtmlTag("td").Text(value.ToString(CultureInfo.InvariantCulture)));
            }

            _table.Append(tr);

            return this;
        }

        public HtmlBuilder FinishTable()
        {
            _html.Body.Append(_table);
            return this;
        }

        public void Finish()
        {
            _html.WriteToFile(_path);
        }
    }
}