function getFile(url){
    return $.ajax(
	      {
		        type     : 'GET',
		        url      : url,
		        timeout  : 20000,
		        cache    : false,
	      });
}

function getJson(url){
    return $.ajax(
	      {
		        type     : 'GET',
		        url      : url,
		        dataType : 'json',
		        timeout  : 20000,
		        cache    : false,
	      });
}

// copied from https://iwb.jp/jquery-javascript-html-escape/
const htmlEscape = (str) => {
    if (!str) return;
    return str.replace(/[<>&"'`]/g, (match) => {
        const escape = {
            '<': '&lt;',
            '>': '&gt;',
            '&': '&amp;',
            '"': '&quot;',
            "'": '&#39;',
            '`': '&#x60;'
        };
        return escape[match];
    });
}

function show_top(){
    getJson('list.json').done(function(data){
        for(f of data.library){
            $('<a>')
                .attr({href: 'status.html?url=' + f})
                .html(f)
                .appendTo('#list');
            $('<br>').appendTo('#list');
        }
    });
}

function format(data){
    data = htmlEscape(data);
    l = data.search("BEGIN CUT HERE") + 15;
    r = data.search(/\n[^\n]*END CUT HERE/);
    return '<pre><code>' + data.substr(l, r - l) + '</code></pre>'
}

function show_content(url){
    var github = 'https://github.com/beet-aizu/library/blob/master'
    $('<a>')
        .attr({href: github + url})
        .html('View on GitHub')
        .appendTo('#github');

    getFile('https://beet-aizu.github.io/library' + url).done(function(data){
        $('#status').html(format(data));
    });
}

$(document).ready(function(){
    $('#top').click(function(){
        window.location.href = 'status.html';
    });

    var query = window.location.search.substring(1);
    if(query.length == 0) {
        show_top();
    }else{
        var url = decodeURIComponent(query.split('&')[0].split('=')[1]);
        show_content(url);
    }
});
