## Usage Declaration
`IDENTIFIER` can be A-Z and _<br>
`VALUE` can be any UTF-8<br>
`NUMBER` can be any digit from 0 to 9<br>
`TEXT` can be any UTF-8 char expect digits (0-9)<br>
if a value type is prefixed by an questionmark, then the Value is Optional. e.g.: `<?VALUE>`

## Command Words

<table>
<thead>
  <tr>
    <th>Usage</th>
    <th>Description</th>
    <th>Version</th>
  </tr>
</thead>
<tbody>
    <tr>
      <td>.ce &lt;NUMBER&gt;<br>First line to center<br>Second line to Center</td>
      <td>Centers NTH next lines</td>
      <td style="text-align: right;">0.1.1-alpha</td>
    </tr>
    <tr>
      <td>.el &lt;?NUMBER&gt;</td>
      <td>Add Empty Line(s). If no argument given, one line will be added</td>
      <td style="text-align: right;">0.1.1-alpha</td>
    </tr>
    <tr>
      <td>.nr &lt;IDENTIFIER&gt; &lt;VALUE&gt;</td>
      <td>Creates a new Register or overwrites its Value</td>
      <td style="text-align: right;">0.1.1-alpha</td>
    </tr>
    <tr>
      <td>.ph<br>&lt;VALUE&gt;</td>
      <td>Creates a paragraph</td>
      <td style="text-align: center;">Not Yet</td>
    </tr>
    <tr>
      <td>.tl '&lt;VALUE&gt;'&lt;VALUE&gt;'&lt;VALUE&gt;'</td>
      <td>Creates a Title</td>
      <td style="text-align: right;">0.1.1-alpha</td>
    </tr>
    <tr>
      <td>.\"&lt;VALUE&gt;</td>
      <td>Creates a Comment, text will not be included in exported Document</td>
      <td style="text-align: right;">0.1.1-alpha</td>
    </tr>
</tbody>
</table>

## Pre Defined Registers

<table class="tg">
<thead>
  <tr>
    <th>Name</th>
    <th>Values</th>
    <th>Description</th>
    <th>Version</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>LL</td>
    <td>Number</td>
    <td>Sets the Line Length of the Document</td>
    <td style="text-align: right;">0.1.1-alpha</td>
  </tr>
  <tr>
    <td>INDENT</td>
    <td>Number</td>
    <td>Sets the depth of Idents (e.g. for Paragraphs or Lists)</td>
    <td>Not Yet</td>
  </tr>
</tbody>
</table>